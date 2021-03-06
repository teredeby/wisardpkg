

class Synthesizer{
public:
  Synthesizer(const std::vector<int>& mentalImage){
    srand(randint(0, 1000000));
    makeCube(mentalImage);
  }

  std::vector<int> make(){
    int index = randint(0, maxData-1);
    std::vector<int> out(cube.size());

    for(unsigned int i=0; i<cube.size(); i++){
      if(cube[i].find(index) == cube[i].end()){
        out[i] = 0;
      }
      else{
        out[i] = cube[i][index];
      }
    }
    return out;
  }

  ~Synthesizer(){
    cube.clear();
  }

private:
  std::vector<std::map<int,int>> cube;
  int maxData;

  void makeCube(const std::vector<int>& mentalImage){
    cube.resize(mentalImage.size());
    maxData = 0;
    for(unsigned int i=0; i<mentalImage.size(); i++){
      if(mentalImage[i]>maxData){
        maxData=mentalImage[i];
      }
    }

    for(unsigned int i=0; i<mentalImage.size(); i++){
      int intensity = mentalImage[i];
      std::vector<int> indexes(maxData);

      for(unsigned int j=0; j<indexes.size(); j++) indexes[j]=j;
      random_shuffle(indexes.begin(),indexes.end());

      for(unsigned int j=0; j<indexes.size(); j++){
        if(intensity == 0) break;
        cube[i][j] = 1;
        intensity--;
      }
    }
  }
};
