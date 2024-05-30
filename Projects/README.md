## Projects Directory List

1. Car_Image_Detection: Car Detection using HOG Features and SVM
2. Digits_MNISTS: MNIST Digit Classification with PyTorch
3. Kal_And_Jinse_Identification: Dog Identification with Mask R-CNN
4. Open_CV_Practice: Exploring Image Transformations and HOG-based Object Detection
5. RC_Drivable_Space: Blue Line Following Robot with Drivable Space Identification (In Progress)
6. TorchVIsion_Fine_Tuning:

## Project Brief Descriptions

### 1. **Car Detection using HOG Features and SVM**

This project demonstrates the use of Histogram of Oriented Gradients (HOG) features and a Support Vector Machine (SVM) classifier to detect cars in images. It includes:

* **HOG Feature Exploration:**  Visualization of HOG features for car and non-car images to understand their representation.
* **SVM Training and Evaluation:** Training an SVM classifier on HOG features, assessing its performance, and saving the model.
* **Car Detection with Sliding Window:**  Implementation of a sliding window search to locate cars in new images, using the trained SVM model.
* **Image Pyramid and Overlapping Box Reduction:**  Enhancements to improve detection by searching at multiple scales and merging overlapping detections.

The project demonstrates the effectiveness of traditional computer vision techniques combined with machine learning for object detection tasks.

Absolutely! Here's a concise summary for your PyTorch MNIST digit classification project:

### 2. **MNIST Digit Classification with PyTorch**

This project demonstrates how to build and train a neural network using PyTorch to classify handwritten digits from the MNIST dataset. Key aspects include:

* **PyTorch Setup:** Utilizes PyTorch and Torchvision for data loading and model construction.
* **Custom Dataset and DataLoader:** Creates a custom dataset class and utilizes dataloaders for efficient data handling.
* **Neural Network Architecture:** Defines a feedforward neural network with multiple layers and ReLU activation functions.
* **Training and Evaluation:** Trains the model, evaluates its accuracy on a test set, and visualizes results with TensorBoard.

This project serves as a foundational example for understanding image classification and working with PyTorch.

### 3. **Dog Identification with Mask R-CNN**

This project showcases a custom-trained Mask R-CNN model designed to identify and distinguish between my two dogs, Kal and Jinse. It involves fine-tuning a pre-trained deep learning model on a labeled dataset of dog images to achieve accurate detection and segmentation. The project demonstrates the potential of adapting powerful object recognition models for specific tasks.

### 4. **Exploring Image Transformations and HOG-based Object Detection**

This project explores fundamental image manipulation techniques, including resizing, cropping, flipping, rotation, and color space conversions. It also delves into gradient calculations and edge detection using Sobel filters and the Canny algorithm. Additionally, the project demonstrates how to use Histogram of Oriented Gradients (HOG) features and a Support Vector Machine (SVM) classifier for detecting objects (in this case, license plates) in images. This serves as a foundational exploration of computer vision principles and techniques.

### 5. **Blue Line Following Robot with Drivable Space Identification (In Progress)**

This project features a Raspberry Pi-powered robot capable of autonomously following a blue line using computer vision. It incorporates the initial development of a neural network model designed to identify drivable terrain for enhanced navigation. Future work involves refining the neural network for accurate drivable space classification.
