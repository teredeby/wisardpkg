
class ClassificationWithWeights: public ClassificationBase {
public:
  ClassificationWithWeights()
    :bleachingActivated(true),confidence(1){}
  ClassificationWithWeights(nl::json config){
    nl::json value;

    value = config["bleachingActivated"];
    bleachingActivated = value.is_null() ? true : value.get<bool>();

    value = config["confidence"];
    confidence = value.is_null() ? 1 : value.get<int>();
  }

  ClassificationWithWeights(const bool bleachingActivated,const int confidence)
    :bleachingActivated(bleachingActivated),confidence(confidence){}

  ClassificationBase* clone() const{
    return new ClassificationWithWeights(bleachingActivated,confidence);
  }

  void setWeights(std::map<std::string,std::vector<int>>& weights){
    this->weights = weights;
  }

  std::map<std::string, int> run(std::map<std::string,std::vector<int>>& allvotes) {
    std::map<std::string, int> labels;
    int bleaching = 0;
    std::tuple<bool,int> ambiguity;

    do{
      int min=0;
      bool firstTime=true;
      for(std::map<std::string,std::vector<int>>::iterator i=allvotes.begin(); i!=allvotes.end(); ++i){
        labels[i->first] = 0;
        for(unsigned int j = 0; j < i->second.size(); j++){
          if(i->second[j] > bleaching){
            labels[i->first] += weights[i->first][j];
            if(firstTime || i->second[j] < min){
              min = i->second[j];
              firstTime = false;
            }
          }
        }
      }
      if(!bleachingActivated) break;
      bleaching = min;
      ambiguity = isThereAmbiguity(labels, confidence);
    }while( std::get<0>(ambiguity) && std::get<1>(ambiguity) > 1 );

    return labels;
  }

  std::string className() const{
    return "ClassificationWithWeights";
  }

  std::string json() const{
    nl::json config = {
      {"bleachingActivated", bleachingActivated},
      {"confidence", confidence},
      {"weights", weights}
    };
    return config.dump();
  }


private:
  bool bleachingActivated;
  int confidence;
  std::map<std::string,std::vector<int>> weights;
};
