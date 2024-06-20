package com.example.robotarm

import android.Manifest
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.BluetoothManager
import android.bluetooth.BluetoothSocket
import android.content.Context
import android.content.pm.PackageManager
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.SeekBar
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import java.io.IOException
import java.util.*

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

    companion object {
        private const val REQUEST_BLUETOOTH_PERMISSIONS = 1
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

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
        isConnected = false
        bluetoothSocket = null
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
    }
}
