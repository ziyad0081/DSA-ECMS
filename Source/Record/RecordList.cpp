#include "../../Headers/Record/RecordList.h"
#include <iomanip>
#include <iostream>

using namespace std;

pair<chrono::system_clock::time_point,chrono::system_clock::time_point>
GetDayPeriodFromMonth(string year_month) throw() {
    //Evil chrono hacks to turn a YYYY/MM into a period by  day and return them as a pair;
    tm time_struct = {};
    istringstream iss(year_month);
    iss >> get_time(&time_struct, "%Y/%m");
    if(iss.fail()) {
        throw invalid_argument("Invalid format was passed to the parser function");
    }
    time_struct.tm_mday = 1; //Set the day of the time struct to the beggining of the month
    auto period_start = chrono::system_clock::from_time_t(mktime(&time_struct));
    //To get the end of the month , we advance the month by 1 then go back by a second to land on the last day. (evil c++ hacks)

    time_struct.tm_mon += 1;
    auto period_end = chrono::system_clock::from_time_t(mktime(&time_struct)) - chrono::seconds(1);
    
    //Returning them as a pair
    return make_pair(period_start,period_end);
}


RecordList::Record::Record(int _consomation, int _injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours):record_date(DateInfo(date, day_weather, max_temp, min_temp, sunny_hours)){
    consomation = _consomation;
    injection = _injection;
    record_date = DateInfo(date,day_weather,max_temp,min_temp,sunny_hours);
    next_record = nullptr;
}
RecordList::Record::~Record(){}

RecordList::RecordList(){
    head_record = tail_record = nullptr;
}

RecordList::~RecordList()
{
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
