# Project: Car Detection using Histogram of Oriented Gradients (HOG) and Support Vector Machines (SVM)

This project explores using traditional computer vision techniques (HOG features) and a machine learning classifier (SVM) to identify cars in images. 

**1. Exploring HOG Features**

* **Goal:** Understand how HOG represents image features by visualizing histograms for car and non-car images.
* **Process:**
    * Load sample car and non-car images from a dataset.
    * Convert images to grayscale.
    * Calculate HOG features using the `skimage.feature.hog` function, which extracts gradient orientations and magnitudes from the image.
    * Display original images alongside their HOG representations. 

**2. Training an SVM Classifier**

* **Goal:** Create a model that can distinguish between car and non-car images based on their HOG features.
* **Process:**
    * **Gather Data:** Load all car and non-car images from the dataset.
    * **Augmentation:** Apply random rotations and scaling to the images to create a more robust dataset.
    * **Extract HOG Features:** Calculate HOG features for all images.
    * **Create Labels:** Assign '1' to car images and '0' to non-car images.
    * **Split Data:** Divide the data into training, validation, and testing sets.
    * **Grid Search:** Use `GridSearchCV` from scikit-learn to find the best hyperparameters (C and kernel type) for the SVM model.
    * **Train Model:** Train the SVM model using the optimal parameters.
    * **Evaluate:** Assess the model's accuracy on the test and validation sets to ensure it's not overfitting.
    * **Save Model:**  Serialize the trained model using `pickle` for later use.

**3. Sliding Window Search**

* **Goal:** Locate cars in new images by applying the SVM model to different regions (windows) within the image.
* **Process:**
    * **Sliding Windows Function:** Define a function `slidingWindows` that systematically generates windows of a fixed size across an image.
    * **Load Model:** Load the saved SVM model.
    * **Prediction Loop:**
        * Extract a window from the image.
        * Compute HOG features for the window.
        * Use the SVM model to predict if the window contains a car.
        * If the prediction is positive and confident (probability >= 0.95), draw a rectangle around the window in the image.

**4. Image Pyramid and Overlapping Box Reduction**

* **Goal:** Improve detection by searching for cars at multiple scales and merging overlapping detections.
* **Process:**
    * **Image Pyramid:** Create multiple scaled-down versions of the image to detect cars of various sizes.
    * **Multi-Scale Search:** Apply the sliding window approach to each scaled image.
    * **Store Detections:** Keep track of all detected car locations.
    * **Overlapping Box Reduction:** Merge overlapping bounding boxes to avoid duplicate detections.
    * **Draw Final Boxes:** Draw the final refined bounding boxes on the image.

**Key Takeaways**

* **HOG Features:** Powerful way to represent the shape and appearance of objects in images.
* **SVM Classifier:** Effective machine learning algorithm for binary classification tasks.
* **Sliding Window:** Technique to scan an image for objects of interest.
* **Image Pyramid:** Helps detect objects at various scales.
* **Overlapping Box Reduction:**  Refines detection results by combining overlapping boxes.