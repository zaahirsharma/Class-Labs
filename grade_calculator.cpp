// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>


// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double reading,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();


    // declare and initialize variables needed
    double exam_sum = 0.0;
    double final_exam = 0.0;
    int total_exam = 0;
    int total_hw = 0;
    double hw_sum = 0;
    int total_lw = 0;
    double lw_sum = 0;
    int total_reading = 0;
    double reading_sum = 0;
    int total_engagement = 0;
    double engagement_sum = 0;
    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry
        if (category == "exam") {
            exam_sum += score;
            total_exam += 1;
        } else if (category == "final-exam") {
            final_exam = score;
            exam_sum += score;
        } else if (category == "hw") {
            hw_sum += score;
            total_hw += 1;
        } else if (category == "lw") {
            lw_sum += score;
            total_lw += 1;
        } else if (category == "reading") {
            reading_sum += score;
            total_reading += 1;
        } else if (category == "engagement") {
            engagement_sum += score;
            total_engagement += 1;
        }else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // compute component averages
    double exam_average = 0.0;
    double hw_average = 0.0;
    double lw_average = 0.0;
    double reading = 0.0;
    double engagement = 0.0;



    exam_average = exam_sum/(total_exam+1);
    if (exam_sum == 0 && final_exam != 0){
        exam_average = final_exam;
    }
    if (exam_average < final_exam){
        exam_average = final_exam;
    }
    if (hw_sum != 0){
        hw_average = hw_sum/total_hw;
    }
    if (lw_sum != 0){
        lw_average = (lw_sum/total_lw)*100;
    }
    if (reading_sum != 0){
        if (reading_sum > 100 || (reading_sum/total_reading + 15) > 100){
            reading = 100;
        }else{
            reading = reading_sum/total_reading + 15;
        }
    }
    if (engagement_sum != 0){
        if (engagement_sum > 100 || (engagement_sum/total_engagement + 15) > 100){
            engagement = 100;
        }else{
            engagement = engagement_sum/total_engagement + 15;
        }
    }


    // compute weighted total of components
    double weighted_total = (exam_average*0.4)+(hw_average*0.4)+(lw_average*0.1)+(reading*0.05)+(engagement*0.05);

    // compute final letter grade
    char final_letter_grade = 'X';
    if (weighted_total >= 90){
        final_letter_grade = 'A';
    } else if (weighted_total < 90 && weighted_total >= 80){
        final_letter_grade = 'B';
    } else if (weighted_total < 80 && weighted_total >= 70){
        final_letter_grade = 'C';
    } else if (weighted_total < 70 && weighted_total >= 60){
        final_letter_grade = 'D';
    } else if (weighted_total < 60){
        final_letter_grade = 'F';
    }
    

    print_results(
        exam_average, hw_average, lw_average, reading, engagement,
        weighted_total, final_letter_grade);
}


void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | reading | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double reading,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "           reading: " << reading << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}
