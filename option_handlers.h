#include <string>

string subjectNameFromOption(int option)
{
    switch (option)
    {
    case 1:
        return "Programming";
        break;

    case 2:
        return "Drafting";
        break;

    case 3:
        return "Data Analysis";
        break;

    case 4: 
        return "Circuits 1";
        break;

    case 5:
        return "Circuits 2";
        break;

    case 6:
        return "OOP";
        break;

    case 7:
        return "Electronics 1";
        break;

    case 8:
        return "Electronics 2";
        break;

    case 9: 
        return "Logic Circuits";
        break;

    case 10:
        return "Microprocessors";
        break;
    
    default:
        return "Invalid option.";
        break;
    }
}

string daysFromDayChoice(string option)
{
    if (!isValidInteger(option)) { 
        cout << option << " is not a valid integer for days choice. ";
        return "";
    }

    switch (stoi(option))
    {
    case 1:
        return "MTh";
        break;

    case 2:
        return "TF";
        break;

    case 3:
        return "M";
        break;

    case 4: 
        return "T";
        break;

    case 5: 
        return "W";
        break;

    case 6:
        return "Th";
        break;

    case 7:
        return "F";
        break;

    case 8: 
        return "S";
        break;
    
    default:
        return "Invalid option.";
        break;
    }
}

string timesFromOptionSingleDay(int option)
{
    switch (option)
    {
    case 1:
        return "08:00-11:00";
        break;

    case 2:
        return "11:00-14:00";
        break;

    case 3:
        return "14:00-17:00";
        break;
    
    default:
        return "Invalid option.";
        break;
    }
}

string timesFromOptionDoubleDay(int option)
{
    switch (option)
    {
    case 1:
        return "08:00-09:30";
        break;

    case 2:
        return "09:30-11:00";
        break;

    case 3:
        return "11:00-12:30";
        break;

    case 4:
        return "12:30-14:00";
        break;

    case 5: 
        return "14:00-15:30";
        break;

    case 6:
        return "15:30-17:00";
        break;
    
    default:
        return "Invalid option";
        break;
    }
}
