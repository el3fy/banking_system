#include "database.h"


qint16 Database:: userID = 0;

Database::Database()
{
    qInfo() << "Hello from dataBase!";
    DataBaseFile = new QFile("myDataBase.json");

    if(!DataBaseFile->exists())
    {
        DataBaseFile->open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(DataBaseFile);

        QJsonObject container;

        QJsonObject l_obj;
        l_obj.insert("UserName", "Admin");
        l_obj.insert("FullName", "Ahmed_Khalifa");
        l_obj.insert("Age", "26");
        l_obj.insert("Password","12345678");
        l_obj.insert("IsAdmin", true);
        l_obj.insert("Balance", "0");

        container.insert("Admin",l_obj);

        QJsonDocument l_doc(container);
        stream << QString::fromUtf8(l_doc.toJson(QJsonDocument::JsonFormat::Indented));
        DataBaseFile->close();
    }

    DBLogger = new Logger("./dbLogger.log");
}

Database &Database::getInstance()
{
    static Database* handler= nullptr;
    if(handler == nullptr)
    {
        handler =new Database();
    }

    return *handler;
}

QJsonObject Database::logIn(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonObject jResponse;
    QJsonParseError jError;

    // Check if the database file exists
    if (!DataBaseFile->exists())
    {
        DBLogger->log("Database file doesn't exist.");
        qCritical() << "Database file doesn't exist.";
        jResponse["logIn_state"] = false;
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }

    // Open the database file for reading
    if (!DataBaseFile->open(QIODevice::ReadOnly))
    {
        DBLogger->log("Failed to open database file for reading.");
        qCritical() << "Failed to open database file for reading.";
        DataBaseFile->close();
        jResponse["logIn_state"] = false;
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }

    // Read JSON content from the database file
    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);
    DataBaseFile->close(); // Close the file after reading

    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        jResponse["logIn_state"] = false;
        jResponse["ResponseID"] = "-1"; // error ID for can't accessing database.
        return jResponse;
    }

    QJsonObject obj = doc.object();

    // Check if the user exists in the database
    if (!obj.contains(data.value("UserName").toString()))
    {
        qCritical() << "User not found.";
        DBLogger->log("User not found.");
        jResponse["logIn_state"] = false;
        jResponse["ResponseID"] = "-2"; //is error ID for user doesn't exist.
        return jResponse;
    }

    // Check if the password matches
    QString userPass = obj.value(data.value("UserName").toString()).toObject().value("Password").toString();
    if (data.value("Password").toString() != userPass)
    {
        qCritical() << "Incorrect password.";
        DBLogger->log("Incorrect password.");
        jResponse["logIn_state"] = false;
        jResponse["ResponseID"] = "-3"; //erro ID for user wrong user name or password.
        return jResponse;
    }

    // Login successful
    bool isAdmin = obj.value(data.value("UserName").toString()).toObject().value("IsAdmin").toBool();
    jResponse["logIn_state"] = true;
    jResponse["ResponseID"] = "0";
    jResponse["IsAdmin"] = isAdmin;
    DBLogger->log("User: " + data.value("UserName").toString() + " has logged in successfully.");
    qInfo() << "User: " + data.value("UserName").toString() + " has logged in successfully.";

    return jResponse;
}


QJsonObject Database::getAccount_Number(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonObject jResponse;
    QJsonParseError jError;

    // Open the database file for reading
    if (!DataBaseFile->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        DBLogger->log("Failed to open database file for reading.");
        qCritical() << "Failed to open database file for reading.";
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }

    // Read JSON content from the database file
    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);
    DataBaseFile->close(); // Close the file after reading

    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }

    QJsonObject obj = doc.object();

    // Check if the user exists in the database
    if (!obj.contains(data.value("UserName").toString()))
    {
        qCritical() << "User not found.";
        DBLogger->log("User not found.");
        jResponse["ResponseID"] = "-2";
        return jResponse;
    }

    // Retrieve the account number of the user
    QString accountNumber = obj.value(data.value("UserName").toString()).toObject().value("AccountNumber").toString();

    // Prepare the response object with the account number
    QJsonObject r_obj;
    r_obj.insert("ResponseID", "1");
    r_obj.insert("AccountNumber", accountNumber);

    qInfo() << "User account number is: " << accountNumber;

    return r_obj;
}


QJsonObject Database::viewAccount_Balance(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonParseError jError;
    QJsonObject jResponse;
    if(!(DataBaseFile->open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qCritical() << "Can't open database file.";
        DBLogger->log("Can't open database file.");
        DataBaseFile->close();
        jResponse["ResponseID"] = "-1";
    }
    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);
    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }
    DataBaseFile->close();


    QJsonObject obj = doc.object();
    QJsonObject r_obj;

    int myFlag{0};
    QString l_Balance;
    foreach(auto key , obj.keys())
    {
        if((obj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber").toString())
        {


            l_Balance = ((obj.value(key)).toObject()).value("Balance").toString();
            myFlag = 1;
            break;
        }
    }
    if(myFlag)
    {
        r_obj.insert("ResponseID", "2");
        r_obj.insert("Balance", l_Balance);
        qInfo() << "The total balance is: " << l_Balance;
    }
    else
    {
        r_obj.insert("ResponseID", "-2");
        qInfo() << "Can't find the user!";
    }
    return r_obj;
}

QJsonObject Database::viewTransaction_History(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonParseError jError;
    QJsonObject jResponse;
    if(!(DataBaseFile->open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qCritical() << "Can't open database file.";
        DBLogger->log("Can't open database file.");
        DataBaseFile->close();
        jResponse["ResponseID"] = "-1";
    }
    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);

    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }
    DataBaseFile->close();
    QJsonObject l_obj = doc.object();

    QString l_key;
    bool myFlag{false};
    foreach(auto key , l_obj.keys())
    {
        if((l_obj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber").toString())
        {
            qInfo() << "User found!";
            l_key = key;
            myFlag = true;
            break;
        }
    }
    if(!myFlag)
    {
        qCritical() << "user not found." << jError.errorString();
        DBLogger->log("user not found.");
        jResponse["ResponseID"] = "-2";
        return jResponse;
    }

    QJsonObject r_obj;
    QJsonArray jArray = ((l_obj.value(l_key)).toObject()).value("TransactionHistory").toArray();

    QJsonArray rArray;
    int count = data.value("Count").toString().toInt();
    if(count > jArray.count())
    {
        count = jArray.count();
    }

    for(int i = jArray.count() - 1; i >=0 ; i--)
    {
        rArray.append(jArray.at(i));
        count--;
        if(count == 0)
        {
            break;
        }
    }

    r_obj.insert("ResponseID", "3");
    r_obj.insert("TransactionHistory", rArray);
    qInfo() << "Transaction History has been sent successfully";
    qInfo() << r_obj.value("TransactionHistory");
    return r_obj;
}

QJsonObject Database::makeTransaction(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonParseError jError;
    QJsonObject jResponse;

    qInfo() << "I'm now in make transaction method!";

    //creating a new transaction.
    QJsonObject transaction;
    double amount = data["Amount"].toString().toDouble();
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy");
    transaction["date"] = date;
    transaction["amount"] = amount;

    if(!(DataBaseFile->open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qCritical() << "Can't open database file.";
        DBLogger->log("Can't open database file.");
        DataBaseFile->close();
        jResponse["ResponseID"] = "-1";
    }

    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);

    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        DataBaseFile->close();
        jResponse["ResponseID"] = "-2";
        return jResponse;
    }
    DataBaseFile->close();

    QJsonObject l_obj = doc.object();
    QString l_key;
    bool myFlag{false};
    foreach(auto key , l_obj.keys())
    {
        if((l_obj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber").toString())
        {
            qInfo() << "User found!";
            l_key = key;
            myFlag = true;
            break;
        }
    }

    if(!myFlag)
    {
        qCritical() << "User's account number doesn't exist.";
        jResponse["ResponseID"] = "-2";
    }
    else
    {

        qInfo() << "we're alright!";
        QJsonObject usrObj =(l_obj.value(l_key)).toObject();
        double l_balance = usrObj.value("Balance").toString().toDouble();
        if((l_balance + amount) < 0)
        {
            qInfo() << "Transaction can't be made.";
            jResponse["ResponseID"] = "-4"; //error ID for Invalid transaction
            return jResponse;
        }

        usrObj["Balance"] = QString::number(l_balance + amount); //updating user's balance.
        QJsonArray usrHistory = usrObj.value("TransactionHistory").toArray();
        usrHistory.append(transaction);
        usrObj["TransactionHistory"]= usrHistory;

        //delete old version..
        // l_obj.remove(l_key);
        l_obj[l_key]= usrObj;

        //writing

        DataBaseFile->open(QIODevice::ReadWrite);
        DataBaseFile->resize(0); // Clear existing content
        QTextStream stream(DataBaseFile);
        stream << QJsonDocument(l_obj).toJson(QJsonDocument::Indented);
        DataBaseFile->close();
        jResponse["UserName"] = l_key;
        jResponse["ResponseID"] = "4";
    }
    return jResponse;
}

QJsonObject Database::transferAmount(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonParseError jError;
    QJsonObject jResponse;

    //creating a new transaction.
    QJsonObject transaction1;
    QJsonObject transaction2;
    double amount = data["Amount"].toString().toDouble();
    QString date = QDateTime::currentDateTime().toString("dd.MM.yyyy");

    transaction1["date"] = date;
    transaction1["amount"] = amount * -1;

    transaction2["date"] = date;
    transaction2["amount"] = amount;

    if(!(DataBaseFile->open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qCritical() << "Can't open database file.";
        DBLogger->log("Can't open database file.");
        DataBaseFile->close();
        jResponse["ResponseID"] = "-1";
    }

    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);

    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }
    DataBaseFile->close();

    QJsonObject l_obj = doc.object();

    bool myFlag_1{false};
    bool myFlag_2{false};

    QString l_key1;
    QString l_key2;

    foreach(auto key , l_obj.keys())
    {
        if((l_obj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber_1").toString())
        {

            qInfo() << "User 1 found!";
            l_key1 = key;
            myFlag_1 = true;
            break;
        }
    }

    foreach(auto key , l_obj.keys())
    {
        if((l_obj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber_2").toString())
        {
            qInfo() << "User 2 found!";
            l_key2 = key;
            myFlag_2 = true;
            break;
        }
    }

    if(!myFlag_1)
    {
        qCritical() << "User 1 can't found.";
        DBLogger->log("User 1 can't found.");
        jResponse["ResponseID"] = "-2";
        return jResponse;
    }

    if(!myFlag_2)
    {
        qCritical() << "User 2 can't found.";
        DBLogger->log("User 2 can't found.");
        jResponse["ResponseID"] = "-2";
        return jResponse;
    }

    QJsonObject usrObj_1 =(l_obj.value(l_key1)).toObject();
    QJsonObject usrObj_2 =(l_obj.value(l_key2)).toObject();

    double l_balance_1 = usrObj_1.value("Balance").toString().toDouble();
    double l_balance_2 = usrObj_2.value("Balance").toString().toDouble();

    if(l_balance_1 < amount)
    {
        qInfo() << "Transaction can't be made.";
        jResponse["ResponseID"] = "-4";
        return jResponse;
    }

    usrObj_1["Balance"] = QString::number(l_balance_1 - amount);
    usrObj_2["Balance"] = QString::number(l_balance_2 + amount);

    QJsonArray usrHistory1 = usrObj_1.value("TransactionHistory").toArray();
    usrHistory1.append(transaction1);
    usrObj_1["TransactionHistory"]= usrHistory1;

    QJsonArray usrHistory2 = usrObj_2.value("TransactionHistory").toArray();
    usrHistory2.append(transaction2);
    usrObj_2["TransactionHistory"]= usrHistory2;

    l_obj[l_key1]= usrObj_1;
    l_obj[l_key2]= usrObj_2;

    DataBaseFile->open(QIODevice::ReadWrite);
    DataBaseFile->resize(0); // Clear existing content
    QTextStream stream(DataBaseFile);
    stream << QJsonDocument(l_obj).toJson(QJsonDocument::Indented);
    DataBaseFile->close();
    jResponse["ResponseID"] = "5";
    qInfo() << "Transfer done successfully";
    return jResponse;
}


QJsonObject Database::viewBankDB(QJsonObject data)
{
    QMutexLocker<QMutex> lock(&mutex);

    QJsonParseError jError;
    QJsonObject jResponse;
    if(!(DataBaseFile->open(QIODevice::ReadOnly | QIODevice::Text)))
    {
        qCritical() << "Can't open database file.";
        DBLogger->log("Can't open database file.");
        DataBaseFile->close();
        jResponse["ResponseID"] = "-1";
    }
    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);
    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON.");
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }
    DataBaseFile->close();
    QJsonObject obj = doc.object();
    obj.insert("ResponseID", "6");
    qInfo() << "Database sent to admin successfully";
    return obj;
}

QJsonObject Database::createUser(QJsonObject data)
{

    QMutexLocker<QMutex> lock(&mutex); // Lock mutex to ensure thread safety
    QJsonObject jResponse;

    // Open the database file
    if (!DataBaseFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qCritical() << "Can't open database file!";
        DBLogger->log("Can't open database file!");
        jResponse["Data_Written"] = false;
        jResponse["NoErrors"] = false;
        jResponse["ResponseID"] = "-1"; // Indication of error state
        return jResponse;
    }

    // Read existing JSON content
    QJsonParseError jError;
    QJsonDocument doc = QJsonDocument::fromJson(DataBaseFile->readAll(), &jError);
    if (jError.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << jError.errorString();
        DBLogger->log("Failed to parse JSON:");
        DataBaseFile->close();
        jResponse["Data_Written"] = false;
        jResponse["NoErrors"] = false;
        jResponse["ResponseID"] = "-1";
        return jResponse;
    }

    DataBaseFile->close();

    // Insert new user data into JSON object
    QJsonObject container = doc.object();

    // Prepare data to be added
    QJsonArray history;
    data["TransactionHistory"] = history;
    userID = QRandomGenerator::global()->bounded(4999);
    data["AccountNumber"] = QString::number(userID);



    foreach (auto id, container)
    {
        if(((container.value(id.toString())).toObject()).value("AccountNumber") == userID)
        {
            data["AccountNumber"] = QString::number(userID);
            continue;
        }
    }


    // check of user existence.
    if(container.contains(data.value("UserName").toString()))
    {
        qCritical() << "Can't create user with this name because it's already exits!.";
        DBLogger->log("User already exits.");
        jResponse["logIn_state"] = false;
        jResponse["ResponseID"] = "-5"; //error ID if the ID is already exists.
        return jResponse;
    }



    // Open the database file again for writing
    if (!DataBaseFile->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        qCritical() << "Can't open database file!";
        DBLogger->log("Can't open database file!");
        jResponse["Data_Written"] = false;
        jResponse["NoErrors"] = false;
        jResponse["ResponseID"] = "-1"; // Indication of error state
        return jResponse;
    }

    // Write the updated JSON to the file
    data.remove("RequestID");
    container.insert(data.value("UserName").toString(), data);
    QJsonDocument writableDoc(container);
    QTextStream stream(DataBaseFile);
    stream << QString::fromUtf8(writableDoc.toJson(QJsonDocument::Indented));
    DataBaseFile->close();

    qInfo() << "User added successfully!";
    jResponse["Data_Written"] = true;
    jResponse["NoErrors"] = true;
    jResponse["ResponseID"] = "7";

    return jResponse;
}


QJsonObject Database::deleteUser(QJsonObject data)
{
    QJsonObject jResponse;
    // Read the JSON file

    if (!DataBaseFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qCritical() << "Failed to open file for reading and writing.";
        jResponse["ResponseID"] = "-1";
        DataBaseFile->close();
        return jResponse;
    }

    // Read JSON content
    QByteArray jsonData = DataBaseFile->readAll();

    // Parse JSON
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << error.errorString();
        jResponse["ResponseID"] = "-1";
        DataBaseFile->close();
        return jResponse;
    }

    QJsonObject jsonObj = jsonDoc.object();
    QString delName;
    int myFlag{0};
    foreach(auto key , jsonObj.keys())
    {
        if((jsonObj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber").toString())
        {
            myFlag = 1;
            delName = (jsonObj.value(key).toObject()).value("UserName").toString();
            qInfo() << "Removing: " << (jsonObj.value(key).toObject()).value("UserName").toString();
            jsonObj.remove((jsonObj.value(key).toObject()).value("UserName").toString());
            break;
        }
    }
    if(myFlag)
    {
        // Write the modified JSON back to the file
        DataBaseFile->resize(0); // Clear existing content
        QTextStream stream(DataBaseFile);
        stream << QJsonDocument(jsonObj).toJson(QJsonDocument::Indented);
        DataBaseFile->close();
        jResponse["ResponseID"] = "8";
        jResponse["DeletedName"] = delName;
        qDebug() << "User" << delName<< "deleted from JSON file successfully.";
        DBLogger->log("User: " + delName + " deleted from JSON file successfully.");
        qInfo() << "User deleted successfully!";
    }
    else
    {
        jResponse.insert("ResponseID", "-2");
        qInfo() << "Can't find the user!";
        DataBaseFile->close();
    }
    return jResponse;
}



QJsonObject Database::updateUser(QJsonObject data)
{
    QJsonObject jResponse;
    // Read the JSON file
    if (!DataBaseFile->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qCritical() << "Failed to open file for reading and writing.";
        jResponse["ResponseID"] = "-1";
        DataBaseFile->close();
        return jResponse;
    }

    // Read JSON content
    QByteArray jsonData = DataBaseFile->readAll();

    // Parse JSON
    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &error);
    if (error.error != QJsonParseError::NoError)
    {
        qCritical() << "Failed to parse JSON:" << error.errorString();
        jResponse["ResponseID"] = "-1";
        DataBaseFile->close();
        return jResponse;
    }

    QJsonObject jsonObj = jsonDoc.object();



    QString upName;
    bool myFlag{false};
    QJsonObject upObj;
    foreach(auto key , jsonObj.keys())
    {
        if((jsonObj.value(key).toObject()).value("AccountNumber").toString() == data.value("AccountNumber").toString())
        {
            //Deleting the old one
            myFlag = true;
            upName = (jsonObj.value(key).toObject()).value("UserName").toString();

            upObj =jsonObj.value(key).toObject();
            if (jsonObj.contains(data.value("UserName").toString()))
            {
                qCritical() << "this user name already exists, can't update.";
                DBLogger->log("this user name already exists, can't update.");
                jResponse["logIn_state"] = false;
                jResponse["ResponseID"] = "-5";
                DataBaseFile->close();
                return jResponse;
            }
            else
            {
                jsonObj.remove(key);
                qInfo() << "Old key deleted successfully";
            }
            break;
        }
    }
    if(myFlag)
    {
        if(data.contains("UserName"))
        {
            // Check if the user exists in the database
            qInfo() << "user name updated";
            upObj["UserName"] = data.value("UserName").toString();
        }
        if(data.contains("Age"))
        {
            qInfo() << "user age updated";
            upObj["Age"] = data.value("Age").toString();
        }
        if(data.contains("Password"))
        {
            qInfo() << "user password updated";
            upObj["Password"] = data.value("Password").toString();

        }
        if(data.contains("FullName"))
        {
            qInfo() << "user full name updated";
            upObj["FullName"] = data.value("FullName").toString();
        }
        jsonObj[upObj.value("UserName").toString()] = upObj;

        // Write the modified JSON back to the file
        DataBaseFile->resize(0); // Clear existing content
        QTextStream stream(DataBaseFile);
        stream << QJsonDocument(jsonObj).toJson(QJsonDocument::Indented);
        DataBaseFile->close();
        jResponse["ResponseID"] = "9";
        jResponse["UpdatedName"] = upName;
        qDebug() << "User" << upName<< "updated from JSON file successfully.";
        DBLogger->log("User: " + upName + " updated from JSON file successfully.");
        qInfo() << "User updated successfully!";
    }
    else
    {
        jResponse.insert("ResponseID", "-2");
        qInfo() << "Can't find the user!";
        DataBaseFile->close();
    }
    return jResponse;
}
