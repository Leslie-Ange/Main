# Main
MAIN REPOSITORY FOR ASSIGNMENTS ON SYSTEMIC PROGRAMMING COURSES
# Student Grade Calculator Application

This application is designed to manage student records, process homework and exam scores, and calculate final grades using either the arithmetic average or the median. 

### Final Grade Formula
The final grade ($Final\_Point$) is calculated using a weighted combination of the homework average (or median) and the final exam grade:

$$Final\_Point = 0.4 \times \left(\frac{1}{n}\sum_{i=1}^{n} HW_i\right) + 0.6 \times Exam$$

Where:
* $HW_i$ represents the grade of individual homework assignments.
* $n$ is the total number of homework assignments.
* $Exam$ represents the final examination grade.
