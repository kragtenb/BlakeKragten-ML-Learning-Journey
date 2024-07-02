package com.example.robotarm

import android.Manifest
import android.R.attr
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.pm.PackageManager
import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.ImageView
import android.widget.SeekBar
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.Job
import kotlinx.coroutines.launch
import kotlinx.coroutines.withContext
import java.io.ByteArrayInputStream
import java.io.IOException
import java.io.InputStream
import java.net.InetSocketAddress
import java.net.Socket
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.util.UUID


class MainActivity : AppCompatActivity() {
    private lateinit var bluetoothManager: BluetoothManager
    private lateinit var bluetoothAdapter: BluetoothAdapter
    private var bluetoothSocket: BluetoothSocket? = null
    private val deviceName = "blakepi"
    private var deviceAddress = ""
    private val uuid: UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB") // Standard RFCOMM UUID
    private var isConnected = false
    private lateinit var connectedStatus: TextView
    private lateinit var connectButton: Button
    private lateinit var seekBarHand: SeekBar
    private lateinit var seekBarWristUpDown: SeekBar
    private lateinit var seekBarWristRotation: SeekBar
    private lateinit var seekBarElbow: SeekBar
    private lateinit var seekBarShoulder: SeekBar
    private lateinit var seekBarBase: SeekBar
    private lateinit var imageView: ImageView
    private lateinit var distanceTextView: TextView

    private var socket: Socket? = null

    private val job = Job()
    private val scope = CoroutineScope(Dispatchers.Main + job)

    companion object {
        private const val REQUEST_BLUETOOTH_PERMISSIONS = 1
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        imageView = findViewById(R.id.imageView)
        distanceTextView = findViewById(R.id.distance_value)

        if (checkAndRequestPermissions()) {
            initializeBluetooth()
        }

        connectedStatus = findViewById(R.id.connected_status)

        val pairedDevices: Set<BluetoothDevice>? = bluetoothAdapter?.bondedDevices
        pairedDevices?.forEach { device ->
            if (deviceName == device.name) {
                deviceAddress = device.address
                Log.i("Main", "Found Device Name: ${device.name} and device address: ${device.address}")
            }
        }

        connectButton = findViewById(R.id.connectButton)
        connectButton.setOnClickListener {
            if (connectButton.text == getString(R.string.disconnect)) {
                closeConnection()
                return@setOnClickListener
            }
            connectToDevice()
//            connectToDeviceOverWifi("192.168.86.46", 8000)
        }

        seekBarHand = findViewById(R.id.seekBarHand)
        seekBarHand.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sendBluetoothMessage("${getString(R.string.hand)} $progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        seekBarWristUpDown = findViewById(R.id.seekBarWristUpDown)
        seekBarWristUpDown.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sendBluetoothMessage("${getString(R.string.wrist_up_down)} $progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        seekBarWristRotation = findViewById(R.id.seekBarWristRotation)
        seekBarWristRotation.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sendBluetoothMessage("${getString(R.string.wrist_rotation)} $progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        seekBarElbow = findViewById(R.id.seekBarElbow)
        seekBarElbow.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sendBluetoothMessage("${getString(R.string.elbow)} $progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        seekBarShoulder = findViewById(R.id.seekBarShoulder)
        seekBarShoulder.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sendBluetoothMessage("${getString(R.string.shoulder)} $progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        seekBarBase = findViewById(R.id.seekBarBase)
        seekBarBase.setOnSeekBarChangeListener(object : SeekBar.OnSeekBarChangeListener {
            override fun onProgressChanged(seekBar: SeekBar?, progress: Int, fromUser: Boolean) {
                sendBluetoothMessage("${getString(R.string.base)} $progress")
            }

            override fun onStartTrackingTouch(seekBar: SeekBar?) {}
            override fun onStopTrackingTouch(seekBar: SeekBar?) {}
        })

        // Start receiving data
        startReceiveBluetoothCoroutine()
        connectToServer("192.168.86.46", 8000)
    }

    private fun startReceiveBluetoothCoroutine() {
        scope.launch(Dispatchers.IO) {
            while (true) {
                if (bluetoothSocket != null && bluetoothSocket!!.isConnected) {
                    try {
                        // Read message type
                        withContext(Dispatchers.IO) {
                            val bluetoothInputStream = bluetoothSocket!!.inputStream
                            val messageTypeBuffer = ByteArray(1)
                            Log.i("BluetoothReceive", "Attempting read")
                            bluetoothInputStream.read(messageTypeBuffer, 0, 1)
                            Log.i("BluetoothReceive", "Finished read")
                            val messageType = messageTypeBuffer[0]

                            when (messageType) {
                                0x02.toByte() -> receiveDistance()
                            }
                        }
                    } catch (e: IOException) {
                        e.printStackTrace()
                    }
                }
            }
        }
    }

    private fun connectToServer(ipAddress: String, port: Int) {
        scope.launch(Dispatchers.IO) {
            while (true) {
                try {
                    Socket(ipAddress, port).use { socket ->
                        val inputStream = socket.getInputStream()
                        while (true) {
                            try {
                                // Read the 0x01 byte
                                val messageType = inputStream.read()
                                if (messageType == -1) {
                                    throw IOException("End of stream reached")
                                }
                                if (messageType != 0x01) {
                                    throw IOException("Invalid message type: $messageType")
                                }

                                // Read the size of the image
                                val lengthBuffer = ByteArray(4)
                                if (inputStream.read(lengthBuffer) != 4) {
                                    throw IOException("Failed to read image length")
                                }
                                val length = ByteBuffer.wrap(lengthBuffer).order(ByteOrder.BIG_ENDIAN).int
                                Log.i("Camera", "Length received for image is $length")

                                // Read the image data
                                val imageBuffer = ByteArray(length)
                                var bytesRead = 0
                                while (bytesRead < length) {
                                    val result = inputStream.read(imageBuffer, bytesRead, length - bytesRead)
                                    if (result == -1) {
                                        throw IOException("End of stream reached while reading image data")
                                    }
                                    bytesRead += result
                                }

                                // Convert byte array to Bitmap
                                val bitmap: Bitmap? = BitmapFactory.decodeByteArray(imageBuffer, 0, length)

                                // Check if the bitmap is not null and set it to the ImageView
                                if (bitmap != null) {
                                    runOnUiThread {
                                        imageView.setImageBitmap(bitmap)
                                    }
                                } else {
                                    Log.e("MainActivity", "Failed to decode image data.")
                                }
                            } catch (e: IOException) {
                                Log.e("MainActivity", "Error receiving image: ${e.message}")
                                break
                            }
                        }
                    }
                } catch (e: IOException) {
                    Log.e("MainActivity", "Connection error: ${e.message}")
                    runOnUiThread {
                        Toast.makeText(this@MainActivity, "Connection error: ${e.message}", Toast.LENGTH_SHORT).show()
                    }
                    // Sleep before attempting to reconnect
                    try {
                        Thread.sleep(5000)
                    } catch (ie: InterruptedException) {
                        Log.e("MainActivity", "Reconnection sleep interrupted: ${ie.message}")
                    }
                }
            }
        }
    }

    private suspend fun receiveDistance() {
        try {
            // Read distance data
            val distanceBuffer = ByteArray(4)
            withContext(Dispatchers.IO) {
                bluetoothSocket!!.inputStream.read(distanceBuffer, 0, 4)
            }
            val distance = ByteBuffer.wrap(distanceBuffer).order(ByteOrder.BIG_ENDIAN).float

            // Update the distance TextView on the main thread
            withContext(Dispatchers.Main) {
                distanceTextView.text = getString(R.string.distance_value, distance)
            }
            Log.i("Distance", "Update distance with frame")
        } catch (e: IOException) {
            e.printStackTrace()
        }
    }

    private fun checkAndRequestPermissions(): Boolean {
        val neededPermissions = arrayOf(
            Manifest.permission.BLUETOOTH,
            Manifest.permission.BLUETOOTH_ADMIN,
            Manifest.permission.BLUETOOTH_CONNECT,
            Manifest.permission.BLUETOOTH_SCAN,
            Manifest.permission.ACCESS_FINE_LOCATION
        )

        val permissionsToRequest = neededPermissions.filter {
            ContextCompat.checkSelfPermission(this, it) != PackageManager.PERMISSION_GRANTED
        }

        return if (permissionsToRequest.isNotEmpty()) {
            ActivityCompat.requestPermissions(this, permissionsToRequest.toTypedArray(), REQUEST_BLUETOOTH_PERMISSIONS)
            false
        } else {
            true
        }
    }

    private fun initializeBluetooth() {
        bluetoothManager = getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
        bluetoothAdapter = bluetoothManager.adapter
    }

    private fun  closeConnection() {
        sendInitValues()
        connectedStatus.setText(R.string.device_disconnected)
        connectButton.setText(R.string.connect_to_device)
        bluetoothSocket?.close()
        socket?.close()
        isConnected = false
        bluetoothSocket = null
        socket = null
        showToast("Connection disconnected")
    }

    private fun sendInitValues() {
        seekBarWristUpDown.progress = 180
        seekBarHand.progress = 0
        seekBarElbow.progress = 180
        seekBarBase.progress = 90
        seekBarWristRotation.progress = 80
        seekBarShoulder.progress = 130
    }

    private fun connectToDeviceOverWifi(ipAddress: String, port: Int) {
        scope.launch(Dispatchers.IO) {
            try {
                socket = Socket()
                socket!!.connect(InetSocketAddress(ipAddress, port), 5000)
            } catch (e: IOException) {
                e.printStackTrace()
                runOnUiThread {
                    Toast.makeText(this@MainActivity, "Connection failed: ${e.message}", Toast.LENGTH_SHORT).show()
                }
                try {
                    socket?.close()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
        }
    }

    private fun connectToDevice() {
        if (bluetoothAdapter.isEnabled) {
            val device = bluetoothAdapter.getRemoteDevice(deviceAddress)
            bluetoothSocket = device.createRfcommSocketToServiceRecord(uuid)
            bluetoothAdapter.cancelDiscovery()
            try {
                bluetoothSocket?.connect()
                isConnected = true
                connectedStatus.setText(R.string.device_connected)
                connectButton.setText(R.string.disconnect)
                sendInitValues()
                showToast("Connected to device")
            } catch (e: IOException) {
                e.printStackTrace()
                connectedStatus.setText(R.string.device_disconnected)
                connectButton.setText(R.string.connect_to_device)
                showToast("Connection failed: ${e.message}")
                try {
                    bluetoothSocket?.close()
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            }
        } else {
            connectedStatus.setText(R.string.device_disconnected)
            connectButton.setText(R.string.connect_to_device)
            showToast("Bluetooth is not enabled")
        }
    }

    private fun sendBluetoothMessage(message: String) {
        if (bluetoothSocket != null) {
            try {
                bluetoothSocket?.outputStream?.write(message.toByteArray())
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }

    private fun showToast(message: String) {
        runOnUiThread {
            Toast.makeText(this, message, Toast.LENGTH_SHORT).show()
        }
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == REQUEST_BLUETOOTH_PERMISSIONS) {
            if (grantResults.all { it == PackageManager.PERMISSION_GRANTED }) {
                initializeBluetooth()
            } else {
                // Handle the case where permissions were not granted
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        closeConnection()
        job.cancel()
    }
}
