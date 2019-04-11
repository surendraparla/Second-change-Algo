#include <iostream>
#include <vector>
using namespace std;

// Split the comma seperated string and make a vector of integers
vector<int> Splitter(string str){
    vector<int> tokens;
    size_t prev = 0, pos = 0;
    string delim = ",";
     while (pos < str.length() && prev < str.length()) {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        tokens.push_back(stoi(token));
        prev = pos + 1;
     }
        return tokens;
}

// Finding a page. if it is present give it a second chance
bool Find(vector<int> &frames, vector<bool> &second_chance, int frame){
    for(int i=0;i<frames.size();i++){
        if(frames[i] == frame) {
            second_chance[i] = true;
            return true;
        }
    }
    return false;
}

// Replacing if some page is not found
static int Replace(vector<int>&frames, vector<bool> &second_chance, int clock, int frame){
    int frame_size = frames.size();
     while(1) 
        { 
            if(!second_chance[clock]) 
            { 
                frames[clock] = frame; 
                return (clock+1)%frame_size; 
            } 
            second_chance[clock] = false; 
            clock = (clock+1)%frame_size; 
        } 
}

// Main Clock Function
int Clock_algo(string sq,int frame_size){
    int pg_faults = 0;
    static int clock = 0;
    vector<int> sequence;
    sequence = Splitter(sq);
    int l = sequence.size();
    vector<int> frames(frame_size, -1);
    vector<bool> second_chance(frame_size, false);
    bool found = true;
    for(int i=0;i<l;i++){
         found = Find(frames, second_chance,sequence[i]);
         if(!found){
            clock = Replace(frames,second_chance, clock, sequence[i]);
            pg_faults++;
         }
    }
    return pg_faults;
}

// Main Function
int main(int argc, char* argv[])
{
    string filename(argv[1]);
    int frameSize = stoi(argv[2]);
    ifstream t(filename);
    string str((istreambuf_iterator<char>(t)),
                 istreambuf_iterator<char>());
	int pgf = 0;
	pgf = Clock_algo(s,frame_size);
	cout<<"No of page faults is: "<<pgf<<endl;
	return 0;
}

