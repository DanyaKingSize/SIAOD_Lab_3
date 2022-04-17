#include <iostream>
#include <fstream>
using namespace std;

class RingList {
private:
    int length;

    class Element {
    public:
        int data;
        Element *next;

    };

    Element *start;
    Element *end;
public:
    //Констркутор лего
    RingList() {
        length = 0;
        start = nullptr;
        end = nullptr;
    }

    //Дестркутор лего

    ~RingList() {
        if (isEmpty()) {
            return;
        }
        end->next = nullptr;
        while (length > 0) {
            Element *temp = start->next;
            start->next = nullptr;
            delete start;
            start = temp;
            length--;
        }

    }


    bool isEmpty() const {
        return length == 0;
    }

    void insertStart(int value) {
        Element *temp = new Element;
        temp->data = value;
        if (isEmpty()) {
            start = temp;
            end = temp;
        } else {
            temp->next = start;
            start = temp;
            end->next = start;


        }
        length++;

    }

    void insertEnd(int value) {
        if (isEmpty()) {
            insertStart(value);
        } else {

            Element *temp = new Element;
            temp->data = value;     //Предыдущий элеменет сейчас end, я в новый кладу значение val
            end->next = temp;       // Предыдущий элемент end указывает на наш новый
            end = temp;             // Новый элемент становится последним
            end->next = start;      // Последний элемент указывает на начало
            length++;
        }


    }

    int readStart() {
        if (isEmpty()) {
            throw length_error("Empty RingList");


        }
        return start->data;
    }

    int readEnd() {
        if (isEmpty()) {
            throw length_error("Empty RingList");
        }
        return end->data;


    }

    int popStart() {
        if (isEmpty()) {
            throw length_error("Empty RingList");
        }

        Element *temp = start->next;
        int x = start->data;
        delete start;
        start = temp;
        end->next = start;
        length--;
        if (isEmpty()) {
            start = nullptr;
            end = nullptr;
        }
        return x;
    }



    //Если всего 1 элемент готово
    // получить ссылку на предпоследний элемент с помщью цикла
    // как сохранить значение последнего элемента
    // Предпоследний указывает на начало

    int popEnd() {
        if (isEmpty()) {
            throw length_error("Empty RingList");
        }
        if (length == 1) {
            return popStart();
        }
        Element *preEnd = start;
        while (preEnd->next != end) {
            preEnd = preEnd->next;
        }
        int x = end->data;
        delete end;
        end = preEnd;
        end->next = start;
        length--;
        cout << end->data<<endl;
        return x;


    }

    void insertPos(int pos, int val) {

        if (isEmpty() && pos != 0) {
            throw length_error("Empty list");
        }


        if (pos > length) {
            pos %= length;
        }

        if (pos == length) {
            insertEnd(val);
            return;
        }
        if (pos == 0) {
            insertStart(val);
            return;
        }


        Element *scroll = start;

        for (int i = 0; i < (pos - 1); i++) {
            scroll = scroll->next;
        }
        Element *temp = new Element();
        temp->data = val;
        temp->next = scroll->next;
        scroll->next = temp;
        length++;


    }

    int getLen() {
        return length;
    }

    int delPose(int pos) {
        if (isEmpty()) {
            throw length_error("Empty list");
        }
        if (pos > length) {
            pos %= length;
        }

        if (pos == (length - 1)) {
            return popEnd();
        }
        if (pos == 0) {
            return popStart();
        }
        Element *scroll = start;
        for (int i = 0; i < (pos - 1); i++) {
            scroll = scroll->next;

        }

        Element *temp = scroll->next;
        scroll->next = temp->next;
        int x = temp->data;
        delete temp;
        length--;
        return x;

    }


    friend std::ostream &operator<<(std::ostream &strm, const RingList &l) {
        Element *q = l.start;
        strm << q->data << " ";

        for (int i = 0; i < l.length - 1; i++) {
            q = q->next;
            strm << q->data << " ";
        }
        return strm;
    }

    int chekRing() {
        if (isEmpty()) {
            throw length_error("Empty list");
        }
        if (length < 3) {
            throw length_error("Too few items in the list");
        }
        Element *temp1 = start;
        Element *temp2 = start->next;
        int x = 0;
        while (temp1 != end) {
            if (temp1->data == temp2->data) {
                x++;

            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        if (start->data == end->data) {
            x++;
        }
        return x;
    }


};

int main() {
    ifstream FileIn("../FileIn.txt");


    if (!FileIn.is_open()){
        cout <<"Error opening file!!!"<<endl;
    }
    else{
        cout << "File open successfully" << endl;
    }

    RingList Rin = RingList();

    int val;
    while(FileIn>>val){

            Rin.insertStart(val);
        }

    cout << Rin << endl;
    cout <<"Zadanie: "<< Rin.chekRing() << endl;
    Rin.insertPos(4, 228);
    cout << Rin << endl;
    cout<<"Deleting start and end  "<<endl;
    Rin.popStart();
    Rin.popEnd();
    cout <<Rin<<endl<<"Deliting pose"<<endl;
    Rin.delPose(3);
    cout << Rin << endl;



    return 0;
}
