**Project Goal:**

Your primary objective was to create an autonomous robot that could:

1.  **Follow a blue line:** Utilize computer vision to detect and navigate along a blue line path.
2.  **Identify drivable space:** Potentially use a neural network to distinguish between areas that are safe for the robot to traverse versus obstacles or non-drivable zones.

**Blue Line Following (Success):**

*   **Hardware:**
    *   Raspberry Pi 4: Served as the robot's brain, handling image processing and motor control.
    *   4 DC Motors: Powered the wheels to move the robot.
    *   Camera: Captured real-time video of the environment.

*   **Software:**
    *   **Python with OpenCV:**
        *   **Image Capture:** Took frames from the camera.
        *   **Color Filtering:** Isolated the blue line using HSV (Hue, Saturation, Value) color space thresholds.
        *   **Contour Detection:** Identified the line's edges.
        *   **Centroid Calculation:** Determined the center of the blue line.
        *   **Steering Logic:** Calculated the necessary adjustments to the motor speeds based on the line's position relative to the center of the camera's view.

**Drivable Space Identification (Work in Progress):**

*   **Concept:**
    *   You intended to employ a neural network to analyze camera images and classify regions as drivable or non-drivable.
*   **Challenges:**
    *   You faced difficulties understanding the neural network implementation at the time, hindering your progress in this aspect of the project.
*   **Future Plans:**
    *   You aim to revisit and complete the drivable space identification functionality once you've deepened your knowledge of neural networks.

**Neural Network Model Development (Initial Steps):**

*   **Data Preparation:**
    *   You created a dataset with images and corresponding masks (annotations) to train the neural network.
    *   The masks were color-coded to represent different classes (drivable, non-drivable, etc.).
*   **Model Selection:**
    *   You chose a pre-trained FCN-ResNet50 model as the base for your neural network due to its strong performance in image segmentation tasks.
*   **Model Modification:**
    *   The model's output layer was adjusted to match your specific number of classes (4 in your case).
*   **Training Process:**
    *   You initiated the training process using your dataset but encountered an early stopping event, indicating that the model's performance was not improving significantly.

**Key Takeaways:**

*   You successfully built a functional blue line following robot using computer vision techniques.
*   You laid the groundwork for implementing a neural network to identify drivable space, but this remains a future task.
*   The project demonstrates your initiative and ability to combine robotics, computer vision, and machine learning concepts.
