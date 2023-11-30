#include "../../Headers/Record/RecordList.h"
#include <iomanip>
#include <iostream>

using namespace std;


RecordList::Record::Record(int _consomation, int _injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours):record_date(DateInfo(date, day_weather, max_temp, min_temp, sunny_hours)){
    consomation = _consomation;
    injection = _injection;
}
RecordList::Record::~Record(){}

RecordList::RecordList(){
    head_record = tail_record = nullptr;
}

RecordList::~RecordList()
{
}

bool RecordList::Record::PrintRecord(){

    cout << setw(13) << setfill(' ') << left << "| Injection |"
         << setw(15) << setfill(' ') << left << "| Consomation |"
         << setw(15) << left << setfill(' ') << "| Date |" << endl;

    cout << setw(13) << internal << setfill(' ') << injection
         << setw(15) << internal<< setfill(' ') << consomation
         << setw(15) << setfill(' ') << record_date.Formatted() << endl;

}

bool RecordList::insertRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours){
    
    auto newRecord = new Record(consomation, injection, date, day_weather, max_temp, min_temp, sunny_hours);
    
    if(!head_record){
        head_record = newRecord;
        tail_record = newRecord;
        return true;
    }
    tail_record->next_record = newRecord;
    tail_record = newRecord;
    return true;
}
