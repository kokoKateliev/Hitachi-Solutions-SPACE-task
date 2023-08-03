#include "ShuttleSchedule.h"
// TASK 1: GET FILE INFORMATION
void ShuttleSchedule::gatherParms(vector<string>& parms) {
    size_t index;
    if (parms[0] == "Day/Parameter") {index = 1;}
    else if (parms[0] == "Temperature (C)") { index = 2; }
    else if (parms[0] == "Wind (m/s)") { index = 3; }
    else if (parms[0] == "Humidity (%)") { index = 4; }
    else if (parms[0] == "Precipitation (%)") { index = 5; }
    else if (parms[0] == "Lightning") { index = 6; }
    else if (parms[0] == "Clouds") { index = 7; }
    else { return; }
    for (size_t i = 1; i < parms.size(); i++) {
        switch (index) {
        case 1:
            dates.push_back(DayProperties(stoi(parms[i])));
            break;
        case 2:
            dates[i - 1].temp = stoi(parms[i]);
            break;
        case 3:
            dates[i - 1].wind = stoi(parms[i]);
            break;
        case 4:
            dates[i - 1].humid = stoi(parms[i]);
            break;
        case 5:
            dates[i - 1].precip = stoi(parms[i]);
            break;
        case 6:
            if (parms[i] == "Yes") {
                dates[i - 1].light = true;
            }
            else {
                dates[i - 1].light= false;
            }
            break;
        case 7:
            dates[i - 1].clouds = parms[i];
            break;
        }
    }

}

void ShuttleSchedule::gatherInformationFromFile(ifstream& inputFile) {
    string line;
    size_t index;
    while (getline(inputFile, line)) {
        stringstream wordsStream(line);
        string word;
        vector<string> parms; //Line parameters
        while (getline(wordsStream, word, ',')) {
            parms.push_back(word);
        }
        gatherParms(parms);
        
    }
}


// TASK 2: GET MOST APPROPRIATE DATE



struct cmp {
    bool operator ()(const DayProperties* a, const DayProperties* b) {
        if (a->wind != b->wind) {
            return a->wind < b->wind;
        }
        return a->humid < b->humid;
    }
};

void ShuttleSchedule::getLaunchingData() {
    vector<DayProperties*> apprDates;
    int testNumbers = 0;
    int testNumbers1 = 1;
    int testNumbers2 = 2;
    for (size_t i = 0; i < dates.size(); ++i) {
        
        if (2 <= dates[i].temp && dates[i].temp <= 31 && dates[i].wind <= 10 && dates[i].humid < 60 && dates[i].precip == 0 && dates[i].light == false && dates[i].clouds != "Cumulus" && dates[i].clouds != "Nimbus") {
            apprDates.push_back(&dates[i]);
        }
    }
    sort(apprDates.begin(), apprDates.end(), cmp());
    bestDay = apprDates[0]->day;
    cout << "Most Approrpriate day: " << bestDay << endl;
}

int ShuttleSchedule::avg(size_t index) {
    int sum = 0;
    int size = dates.size();
    for (size_t i = 0; i < size; i++) {
        switch (index) {
        case 1:
            sum += dates[i].temp;
            break;
        case 2:
            sum += dates[i].wind;
            break;
        case 3:
            sum += dates[i].humid;
            break;
        case 4:
            sum += dates[i].precip;
            break;
        default:
            break;
        }
    }
    return sum/size;
}

int ShuttleSchedule::max(size_t index) {
    int maxV = INT_MIN;
    int size = dates.size();
    for (size_t i = 0; i < size; i++) {
        switch (index) {
        case 1:
            if (maxV < dates[i].temp) {
                maxV = dates[i].temp;
            }
            break;
        case 2:
            if (maxV < dates[i].wind) {
                maxV = dates[i].wind;
            }
            break;
        case 3:
            if (maxV < dates[i].humid) {
                maxV = dates[i].humid;
            }
            break;
        case 4:
            if (maxV < dates[i].precip) {
                maxV = dates[i].precip;
            }
            break;
        default:
            break;
        }
    }
    return maxV;
}

int ShuttleSchedule::min(size_t index) {
    int minV = INT_MAX;
    int size = dates.size();
    for (size_t i = 0; i < size; i++) {
        switch (index) {
        case 1:
            if (minV > dates[i].temp) {
                minV = dates[i].temp;
            }
            break;
        case 2:
            if (minV > dates[i].wind) {
                minV = dates[i].wind;
            }
            break;
        case 3:
            if (minV > dates[i].humid) {
                minV = dates[i].humid;
            }
            break;
        case 4:
            if (minV > dates[i].precip) {
                minV = dates[i].precip;
            }
            break;
        default:
            break;
        }
    }
    return minV;
}

int ShuttleSchedule::median(size_t index) {
    vector<int> values;
    int size = dates.size();
    for (size_t i = 0; i < size; i++) {
        switch (index) {
        case 1:
            values.push_back(dates[i].temp);
            break;
        case 2:
            values.push_back(dates[i].wind);
            break;
        case 3:
            values.push_back(dates[i].humid);
            break;
        case 4:
            values.push_back(dates[i].precip);
            break;
        default:
            break;
        }
    }
    sort(values.begin(), values.end());
    if (values.size() == 1) {
        return values[0];
    }
    if (values.size() % 2 != 0) {
        return values[(values.size() / 2) + 1];
    }
    else {
        return (values[(values.size() / 2)] + values[(values.size() / 2) + 1]) / 2;
    }
}

void ShuttleSchedule::writeInformationToFile() {
    getLaunchingData();
    ofstream writeFile("WeatherReport.csv");
    writeFile << "Parameters," << "Average value," << "Max value," << "Min value," << "Median value," << endl;
    writeFile << "Temperature(C)," << avg(1) << "," << max(1) << "," << min(1) << "," << median(1) << "," << endl;
    writeFile <<"Wind(m/s)," << avg(2) << "," << max(2) << "," << min(2) << "," << median(2) << "," << endl;
    writeFile <<"Humidity(%)," << avg(3) << "," << max(3) << "," << min(3) << "," << median(3) << "," << endl;
    writeFile <<"Precipitation(%)," << avg(4) << "," << max(4) << "," << min(4) << "," << median(4) << "," << endl;
    writeFile <<"Lightning," << "-," << "-," << "-," << "-," << endl;
    writeFile << "Clouds," << "-," << "-," << "-," << "-," << endl;
    if (bestDay != -1) {
        writeFile << "The most appropriate launch day," << bestDay << endl;
    }
}