**Project: Dog Identification with Fine-Tuned Mask R-CNN**

This project focuses on building a custom model to identify and distinguish between my two dogs, Kal and Jinse, using a fine-tuned Mask R-CNN architecture.

[Video Link](https://photos.app.goo.gl/rAepD1wVMe8wfirz8)

**1. Data Preparation**

* **Image Collection:** I gathered approximately 80 photos of my dogs in various poses, lighting conditions, and environments.
* **Labeling with CVAT.ai:** I utilized CVAT.ai, an open-source annotation tool, to manually draw bounding boxes and segmentation masks around Kal and Jinse in each image. The masks delineate the precise pixels belonging to each dog.

**2. Custom Dataset and Dataloader**

* **Goal:** Create a custom PyTorch dataset (`KalAndJinseDataset`) to load and preprocess the labeled images and masks.
* **Process:**
    * Read image and mask files from the respective directories.
    * Convert pixel values in the masks to unique class labels (1 for Kal, 2 for Jinse).
    * Generate bounding boxes from the masks using `torchvision.ops.masks_to_boxes`.
    * Organize the data into a dictionary format required by the Mask R-CNN model, including boxes, masks, labels, image IDs, areas, and crowd information.
    * Apply data augmentation transformations (e.g., random horizontal flips) during training.

**3. Model Selection and Modification**

* **Goal:** Choose a pre-trained Mask R-CNN model and adapt it for the dog identification task.
* **Process:**
    * Load a pre-trained Mask R-CNN model with ResNet-50 backbone using `torchvision.models.detection.maskrcnn_resnet50_fpn`.
    * Modify the last layer of the model's box predictor (`roi_heads.box_predictor`) and mask predictor (`roi_heads.mask_predictor`) to output three classes (background, Kal, Jinse).
    * Replace the pre-trained predictors with new `FastRCNNPredictor` and `MaskRCNNPredictor` instances.

**4. Model Training and Evaluation**

* **Goal:** Fine-tune the model on the labeled dataset and evaluate its performance.
* **Process:**
    * Split the dataset into training and test sets.
    * Define a training loop using `train_one_epoch` from the `engine` module (likely a custom utility).
    * Employ stochastic gradient descent (SGD) optimizer and a learning rate scheduler.
    * Train for a set number of epochs, periodically evaluating the model's accuracy on the test set.

**5. Real-time Detection**

* **Goal:** Deploy the trained model to perform real-time dog identification using a webcam.
* **Process:**
    * Load the saved model's state dictionary.
    * Capture video frames from the webcam.
    * Preprocess each frame (resize, convert to tensor, apply transformations).
    * Run inference using the model to obtain predictions (bounding boxes, masks, labels, scores).
    * Filter predictions based on a confidence threshold.
    * Draw bounding boxes, masks, and labels on the frame for visualization.
    * Display the resulting frame with detections.

**Key Points:**

* **Transfer Learning:** Leveraging a pre-trained Mask R-CNN model accelerated the training process and improved performance.
* **Data Labeling:** The quality of annotations (bounding boxes and masks) is crucial for accurate object detection and segmentation.
* **Custom Dataset:** A well-structured custom dataset facilitates seamless integration with PyTorch's data loading and training pipeline.

This project demonstrates the capability of fine-tuning state-of-the-art deep learning models for specific tasks, opening up possibilities for various object recognition applications.
