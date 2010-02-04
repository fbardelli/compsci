//template<class TYPE>
template<class TYPE>
class Elements {
  public:
    Elements(int s=1);
    ~Elements();
    void set(int index, TYPE value);
    TYPE get(int index);
    int getSize();
  private:
    TYPE *data;
    int size;
};


template<class TYPE> Elements<TYPE>::Elements(int s):size(s){
  data = new TYPE[size];
}

template<class TYPE> Elements<TYPE>::~Elements(){
  delete[] data;
}

template<class TYPE> void Elements<TYPE>::set(int index, TYPE value){
  data[index] = value;
}

template<class TYPE> TYPE Elements<TYPE>::get(int index){
  return data[index];
}

template<class TYPE> int Elements<TYPE>::getSize(){
  return size;
}

