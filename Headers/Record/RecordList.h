#pragma once

#include <iostream>
using namespace std;



struct DateInfo {
            string date;
            string day_weather;
            unsigned int max_temp;
            unsigned int min_temp;
            unsigned int sunny_hours;

            DateInfo(string _date ,string _day_weather , int _max_temp, int _min_temp, int sunny_hrs){
                
                date = _date;
                //Parsing the string we have into the date array
                day_weather = _day_weather;
                max_temp = _max_temp;
                min_temp = _min_temp;
                sunny_hours = sunny_hrs;
            }

            string Formatted(){
                return date;
            }
};

class RecordList
{
    public:
        class Record{
            public:
                friend class Customer;
                friend class RecordList;
                Record(int _consomation, int _injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours);
                ~Record();
                float   GetNetCost(); //This retrieves the net price for the daily transaction of the customer
                bool    PrintRecord();
                Record*  next_record;

            private:
                float    consomation;
                float    injection;
                DateInfo record_date;

        };


        RecordList();
        ~RecordList();

        bool insertRecord(int consomation, int injection, string date, string day_weather, int max_temp, int min_temp, int sunny_hours);

        Record* head_record;
        Record* tail_record;

};
