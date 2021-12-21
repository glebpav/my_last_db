#include "dataholder.h"

DataHolder::DataHolder(){}

DataHolder::DataHolder(string key, string value){
    this->key = key;
    this->value = value;
}

DataHolder::DataHolder(string key, string value, string dataType){
    this->key = key;
    this->value = value;
    this->dataType =dataType;
}

void DataHolder::setKey(string key){
    this->key = key;
}

void DataHolder::setValue(string value){
    this->value = value;
}

void DataHolder::setdataType(string dataType){
    this->dataType = dataType;
}

string DataHolder::getKey(){
    return key;
}

string DataHolder::getValue(){
    return value;
}

string DataHolder::getDataType(){
    return dataType;
}
