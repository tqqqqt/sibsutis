#include <QtTest>

#include "../TelephoneBook/src/abonentlist.h"

class t_abonentList : public QObject
{
    Q_OBJECT

public:
    t_abonentList();
    ~t_abonentList();

private slots:
    void test_add();

    void test_findName_1();
    void test_findName_2();

    void test_clear();

    void test_getAll();

    void test_getElem_1();
    void test_getElem_2();

    void test_deleteElem_1();
    void test_deleteElem_2();

    void test_updateElem_1();
    void test_updateElem_2();
};

t_abonentList::t_abonentList(){ }
t_abonentList::~t_abonentList(){ }

void t_abonentList::test_add(){
    AbonentList object;
    std::string input_name="Al", input_phone="228";
    std::string curent_name="", curent_phone="";
    QString name="Al", phone="228";

    object.add(input_name,input_phone);
    object.getElem(0,curent_name,curent_phone);

    QCOMPARE(QString::fromStdString(curent_name),name);
    QCOMPARE(QString::fromStdString(curent_phone),phone);
}

void t_abonentList::test_findName_1(){
    AbonentList object;
    std::string input_name="Al", input_phone="228";
    int curent_index=0, index=-1;

    object.add(input_name,input_phone);
    curent_index=object.findName("Hello");

    QCOMPARE(curent_index,index);
}

void t_abonentList::test_findName_2(){
    AbonentList object;
    std::string input_name="Al", input_phone="228";
    int curent_index=0, index=0;

    object.add(input_name,input_phone);
    curent_index=object.findName(input_name);

    QCOMPARE(curent_index,index);
}

void t_abonentList::test_clear(){
    AbonentList object;
    std::string input_name="Al", input_phone="228";
    int curent_index=0, index=-1;

    object.add(input_name,input_phone);
    object.clear();
    curent_index=object.findName(input_name);

    QCOMPARE(curent_index,index);
}

void t_abonentList::test_getAll(){
    AbonentList object;
    std::vector<std::string> cur_res, res{"Al","228","Hen","446","Tem","337"};

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);
    cur_res=object.getAll();

    QCOMPARE(cur_res.size(),res.size());
    for(int i=0;i<res.size();++i){
        QCOMPARE(cur_res[i].c_str(),res[i].c_str());
    }
}

void t_abonentList::test_getElem_1(){
    AbonentList object;
    std::vector<std::string> res{"Al","228","Tem","337","Hen","446"};
    int input_index=5;
    std::string buf, result="incorect index";

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);

    try{
        object.getElem(input_index,buf,buf);
        QCOMPARE(1,0);
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.c_str());
    }
}

void t_abonentList::test_getElem_2(){
    AbonentList object;
    std::vector<std::string> res{"Al","228","Hen","446","Tem","337"};
    int input_index=1;
    std::string cur_name="", cur_phone="";

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);
    object.getElem(input_index,cur_name,cur_phone);

    QCOMPARE(cur_name.c_str(),res[input_index*2].c_str());
    QCOMPARE(cur_phone.c_str(),res[input_index*2+1].c_str());
}

void t_abonentList::test_deleteElem_1(){
    AbonentList object;
    std::vector<std::string> res{"Al","228","Tem","337","Hen","446"};
    int input_index=5;
    std::string result="incorect index";

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);

    try{
        object.deleteElem(input_index);
        QCOMPARE(1,0);
    }
    catch(std::exception &exp){
        QCOMPARE(exp.what(),result.c_str());
    }
}

void t_abonentList::test_deleteElem_2(){
    AbonentList object;
    std::vector<std::string> cur_res, res{"Al","228","Hen","446","Tem","337"};
    int input_index=0;

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);
    object.deleteElem(input_index);
    cur_res=object.getAll();

    for(int i=0;i<cur_res.size();++i){
        QCOMPARE(cur_res[i].c_str(),res[i+2].c_str());
    }
}

void t_abonentList::test_updateElem_1(){
    AbonentList object;
    std::vector<std::string> cur_res, res{"Al","228","Hen","446","Tem","337"};
    int input_index=66;
    std::string result="incorect index";

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);

    try{
        object.updateElem(input_index,"","");
        QCOMPARE(1,0);
    }
    catch(std::exception& exp){
        QCOMPARE(exp.what(),result.c_str());
    }
}

void t_abonentList::test_updateElem_2(){
    AbonentList object;
    std::vector<std::string> cur_res, res{"Al","228","Hen","446","Tem","337"};
    int input_index=0;
    std::string res_name="Abba", res_phone="227";
    std::string cur_name="", cur_phone="";

    for(int i=0;i<res.size();i+=2) object.add(res[i],res[i+1]);
    object.updateElem(input_index,res_name,res_phone);
    object.getElem(input_index,cur_name,cur_phone);

    QCOMPARE(cur_name.c_str(),res_name.c_str());
    QCOMPARE(cur_phone.c_str(),res_phone.c_str());
}

QTEST_APPLESS_MAIN(t_abonentList)

#include "tst_t_abonentlist.moc"
