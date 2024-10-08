// COMSC-210 | Abstract & Automate Lab 18 | Yukun Zhang
// IDE used: Visual Studio Code

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<ctime>    
#include<cstdlib>  
#include<iomanip>  
using namespace std;

struct ReviewNode{
    float rating;        // Store rating
    string comment;      // Store review comment
    ReviewNode* next;    // Pointer to the next review
};

class Movie{
private:
    string title;               // Movie title
    ReviewNode* reviewsHead;     // Linked list of reviews

public:
    // Constructor
    Movie(string movieTitle): title(movieTitle), reviewsHead(nullptr){}
    // Destructor to clean up memory
    ~Movie(){
        ReviewNode* current = reviewsHead;
        while(current){
            ReviewNode* next = current->next;
            delete current;
            current = next;
        }
    }
    // Function to add a review at the head of the linked list
    void addReview(float rating,const string& comment){
        ReviewNode* newNode = new ReviewNode{rating,comment,reviewsHead};
        reviewsHead = newNode;
    }

    // Function to output all reviews for the movie
    void outputReviews()const{
        cout<<"Movie: "<<title<<endl;
        if(!reviewsHead){
            cout<<"No reviews available.\n";
            return;
        }
        ReviewNode* current = reviewsHead;
        int count = 1;
        while(current){
            cout<<"> Review #"<<count++<<": "<<fixed<<setprecision(1)
                <<current->rating<<": "<<current->comment<<endl;
            current = current->next;
        }
        cout<<endl;
    }
};

// Function to generate a random rating between 1.0 and 5.0
float generateRandomRating(){
    return 1.0f + static_cast<float>(rand() % 41) / 10.0f;  // Generates between 1.0 and 5.0
}

// Function to load reviews from an external file and add them to the movie
void loadReviewsFromFile(Movie& movie,const string& filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr<<"Failed to open file: "<<filename<<endl;
        return;
    }
    string comment;
    while(getline(file,comment)){
        float rating = generateRandomRating(); // Generate random rating for each review
        movie.addReview(rating,comment);      // Add the review to the movie's linked list
    }
    file.close();
}

int main(){
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
    // Create a vector of Movie objects
    vector<Movie> movies = {
        Movie("The Shawshank Redemption"),
        Movie("The Godfather"),
        Movie("The Dark Knight"),
        Movie("Pulp Fiction")
    };
    // Load reviews for each movie from corresponding files
    loadReviewsFromFile(movies[0],"shawshank_reviews.txt");
    loadReviewsFromFile(movies[1],"godfather_reviews.txt");
    loadReviewsFromFile(movies[2],"dark_knight_reviews.txt");
    loadReviewsFromFile(movies[3],"pulp_fiction_reviews.txt");
    // Output reviews for each movie
    for(const auto& movie : movies){
        movie.outputReviews();
    }
    return 0;
}

