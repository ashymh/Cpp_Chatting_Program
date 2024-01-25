#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h> //Winsock ������� include. WSADATA �������.
#include <WS2tcpip.h>
#include <string>
#include <sstream>
#include <iostream>
#include <thread>
#include <mysql/jdbc.h>
#include <conio.h> 
#include <Windows.h>

#define MAX_SIZE 1024

using std::cout;
using std::cin;
using std::endl;
using std::string;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "1234";

sql::mysql::MySQL_Driver* driver; // ���� �������� �ʾƵ� Connector/C++�� �ڵ����� ������ �� 
sql::Connection* con;
sql::PreparedStatement* pstmt;
sql::ResultSet* result;
sql::Statement* stmt;

SOCKET client_sock;
string my_nick;



void startMenu() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       1. �α���                            ��" << endl;
    cout << "��                       2. ID ã��                           ��" << endl;
    cout << "��                       3. PW ã��                           ��" << endl;
    cout << "��                       4. ȸ������                          ��" << endl;
    cout << "��                       0. ����                              ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void login() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                          �α���                            ��" << endl;
    cout << "��                       1. ID �Է�                           ��" << endl;
    cout << "��                       2. PW �Է�                           ��" << endl;
    cout << "��                       >> �Ϸ�� �α���!                    ��" << endl;
    cout << "��                       >> ���н� ����ȭ��                   ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void searchId() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                        ���̵� ã��                         ��" << endl;
    cout << "��                       >> �̸� �Է�                         ��" << endl;
    cout << "��                       >> ��ȣ �Է�                         ��" << endl;
    cout << "��                       >> �������(8�ڸ�) �Է�              ��" << endl;
    cout << "��                       >> �Ϸ�� ���̵� ���                ��" << endl;
    cout << "��                       >> ���н� ����ȭ��                   ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void searchPw() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                       ��й�ȣ ã��                        ��" << endl;
    cout << "��                       >> ���̵� �Է�                       ��" << endl;
    cout << "��                       >> ��й�ȣ �Է�                     ��" << endl;
    cout << "��                       >> �������(8�ڸ�) �Է�              ��" << endl;
    cout << "��                       >> ��ȭ��ȣ �Է�                     ��" << endl;
    cout << "��                       >> �Ϸ�� ����ȭ��                   ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void createUser() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                         ȸ������                           ��" << endl;
    cout << "��                       >> ���̵� �Է�                       ��" << endl;
    cout << "��                       >> ��й�ȣ �Է�                     ��" << endl;
    cout << "��                       >> �̸�, ��ȭ��ȣ �Է�               ��" << endl;
    cout << "��                       >> �������(8�ڸ�) �Է�              ��" << endl;
    cout << "��                       >> �Ϸ�� ����ȭ��                   ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void mainMenu() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       1. ������                            ��" << endl;
    cout << "��                       2. ģ�� ���                         ��" << endl;
    cout << "��                       3. ä�ù� ����                       ��" << endl;
    cout << "��                       0. ����                              ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void myProfile() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                        ������ ����                         ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       1. �� ������                         ��" << endl;
    cout << "��                       2. ���¸޼��� ����/����              ��" << endl;
    cout << "��                       0. ����                              ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void friends() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                        ��ģ�� ����                         ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       1. ģ�� ���                         ��" << endl;
    cout << "��                       0. ����                              ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void chattinginfo() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       ä�� ���α׷�                        ��" << endl;
    cout << "��                        ä�ù� ���                         ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                       1. ä�� �ϱ�                         ��" << endl;
    cout << "��                       2. ä�� ���� �˻�                    ��" << endl;
    cout << "��                       0. �ڷΰ���                          ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
void chattingmain() {
    system("cls");
    cout << "���������������������������������" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                        ä�ù� ����!!                       ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "��                           /����                            ��" << endl;
    cout << "��                                                            ��" << endl;
    cout << "���������������������������������" << endl;
}
int chat_recv() {
    char buf[MAX_SIZE] = { };
    string msg;

    while (1) {
        ZeroMemory(&buf, MAX_SIZE);

        if (recv(client_sock, buf, MAX_SIZE, 0) > 0) {
            msg = buf;
            std::stringstream ss(msg);  // ���ڿ��� ��Ʈ��ȭ
            string user;
            ss >> user; // ��Ʈ���� ����, ���ڿ��� ���� �и��� ������ �Ҵ�. ���� ����� �̸��� user�� �����.
            if (user != my_nick) cout << buf << endl; // ���� ���� �� �ƴ� ��쿡�� ����ϵ���.
        }
        else {
            cout << "Server Off" << endl;
            return -1;
        }
    }
}

class SQL {
private:
    string id, pw, name, phone, status, birth;
public:
    SQL()
    {
        try {
            driver = sql::mysql::get_mysql_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException& e) {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            exit(1);
        }

        con->setSchema("project2");

        // DB �ѱ� ������ ���� ����
        stmt = con->createStatement();
        stmt->execute("set names euckr");
        if (stmt) { delete stmt; stmt = nullptr; }
    }
    int login() {
        cout << ">>���̵� : ";
        cin >> id;
        this->id = id;
        cout << ">>��й�ȣ�� �Է����ּ��� : ";
        char ch = ' ';
        while (ch != 13) { // Enter Ű�� ������ �Է� ����
            ch = _getch();
            if (ch == 13) break; // Enter Ű�� ������ �Է� ����
            else if (ch == 8) { 
                if (!pw.empty()) { 
                    pw.pop_back(); 
                    cout << "\b \b"; 
                }
            }
            else {
                pw.push_back(ch);
                cout << '*'; // ��ǥ�� ��ü�Ͽ� ���
            }
        }
        cout << endl;
        pstmt = con->prepareStatement("SELECT id, pw, name FROM user WHERE id=?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) { // ���� ����� �ִٸ�
            string db_id = result->getString(1); // �����ͺ��̽����� ������ ID
            string db_pw = result->getString(2); // �����ͺ��̽����� ������ PW

            if (db_id == id && db_pw == pw) {
                name = result->getString(3);
                cout << endl << "���α��� ���Դϴ�. ��ø� ��ٷ��ּ���." << endl << endl;

                cout << "��" << name << "�� ȯ���մϴ�." << endl;
                return 1;
            }
            else cout << "���ش��ϴ� ������ �����ϴ�." << endl;
        }
        else cout << "���ش��ϴ� ������ �����ϴ�." << endl;
        pw.clear();
    }
    void searchId() {
        cout << ">>�̸� : ";
        cin >> name;
        cout << ">>��ȭ��ȣ : ";
        cin >> phone;
        while (true) {
            cout << ">>������� : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "����������� 8�ڸ��� �Է����ּ���." << endl;
                continue;
            }
            break;
        }

        string year = birth.substr(0, 4);
        string month = birth.substr(4, 2);
        string day = birth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("SELECT id, name, phone, birth FROM user WHERE phone=?");
        pstmt->setString(1, phone);
        result = pstmt->executeQuery();

        if (result->next()) {
            string db_id = result->getString(1);
            string db_name = result->getString(2);
            string db_phone = result->getString(3);
            string db_birth = result->getString(4);

            if (db_name == name && db_phone == phone && db_birth == DATE) {
                cout << "��" << name << "���� ���̵�� " << db_id << "�Դϴ�." << endl;
                Sleep(3000);
            }
            else {
                cout << "���ش��ϴ� ������ �����ϴ�.!" << endl;
                Sleep(500);
            }
        }
        else {
            cout << "���ش��ϴ� ������ �����ϴ�.?" << endl;
            Sleep(500);
        }
    }
    void searchPw() {
        cout << ">>���̵� : ";
        cin >> id;
        cout << ">>�̸� : ";
        cin >> name;
        cout << ">>��ȭ��ȣ : ";
        cin >> phone;
        while (true) {
            cout << ">>������� : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "����������� 8�ڸ��� �Է����ּ���." << endl;
                continue;
            }
            break;
        }

        string year = birth.substr(0, 4);
        string month = birth.substr(4, 2);
        string day = birth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("SELECT id, name, phone, birth FROM user WHERE id=?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        if (result->next()) {
            string db_id = result->getString(1);
            string db_name = result->getString(2);
            string db_phone = result->getString(3);
            string db_birth = result->getString(4);

            if (db_id == id && db_name == name && db_phone == phone && db_birth == DATE) {
                while (1) {
                    string new_pw = "";
                    cout << ">>���ο� ��й�ȣ�� �Է����ּ��� : ";
                    char ch = ' ';
                    while (ch != 13) { // Enter Ű�� ������ �Է� ����
                        ch = _getch();
                        if (ch == 13) break; // Enter Ű�� ������ �Է� ����
                        if (ch == 8) { // Backspace Ű�� ���
                            if (!new_pw.empty()) { // �Էµ� ���ڰ� ������
                                new_pw.pop_back(); // ������ ���ڸ� ����
                                cout << "\b \b"; // Ŀ�� ��ġ�� �������� �̵����� ������ ����� ��, �ٽ� Ŀ�� ��ġ�� ������� �̵���Ŵ
                            }
                        }
                        else {
                            new_pw.push_back(ch);
                            cout << '*'; // ��ǥ�� ��ü�Ͽ� ���
                        }
                    }


                    cout << endl;

                    string renew_pw = "";
                    cout << ">>�ٽ� �ѹ� �Է����ּ���. : ";
                    char rech = ' ';
                    while (rech != 13) { // Enter Ű�� ������ �Է� ����
                        rech = _getch();
                        if (rech == 13) break; // Enter Ű�� ������ �Է� ����
                        if (rech == 8) { // Backspace Ű�� ���
                            if (!renew_pw.empty()) { // �Էµ� ���ڰ� ������
                                renew_pw.pop_back(); // ������ ���ڸ� ����
                                cout << "\b \b"; // Ŀ�� ��ġ�� �������� �̵����� ������ ����� ��, �ٽ� Ŀ�� ��ġ�� ������� �̵���Ŵ
                            }
                        }
                        else {
                            renew_pw.push_back(rech);
                            cout << '*'; // ��ǥ�� ��ü�Ͽ� ���
                        }
                    }
                    cout << endl;

                    if (new_pw == renew_pw) {
                        pstmt = con->prepareStatement("UPDATE user SET pw = ? WHERE id = ?");
                        pstmt->setString(1, new_pw);
                        pstmt->setString(2, id);
                        pstmt->executeQuery();
                        printf("�����ο� ��й�ȣ�� ����Ǿ����ϴ�.\n");
                        Sleep(500);
                        break;
                    }
                    else {
                        cout << "����й�ȣ�� �ٸ��ϴ�." << endl;
                        Sleep(500);
                    }
                }
            }
            else {
                cout << "���ش��ϴ� ������ �����ϴ�." << endl;
                Sleep(500);
            }
        }
        else {
            cout << "���ش��ϴ� ������ �����ϴ�." << endl;
            Sleep(500);
        }
    }
    void createUser() {
        while (1) {
            cout << ">>���̵� : ";
            cin >> id;
            pstmt = con->prepareStatement("SELECT id FROM user WHERE id=?");
            pstmt->setString(1, id);
            result = pstmt->executeQuery();

            if (result->next()) {
                string db_id = result->getString(1);
                if (db_id == id) {
                    cout << "���ߺ��� ���̵� �ֽ��ϴ�." << endl;
                    continue;
                }
            }
            else {
                cout << "�ߺ�üũ �Ϸ�." << endl;
                break;
            }
        }
        while (1) {
            cout << ">>��й�ȣ�� �Է����ּ��� : ";
            char ch = ' ';
            while (ch != 13) { 
                ch = _getch();
                if (ch == 13) break; 
                if (ch == 8) { 
                    if (!pw.empty()) { 
                        pw.pop_back(); 
                        cout << "\b \b";
                    }
                }
                else {
                    pw.push_back(ch);
                    cout << '*'; // ��ǥ�� ��ü�Ͽ� ���
                }
            }
            cout << endl;
            string new_pw = "";
            cout << endl << ">>�ٽ� �ѹ� �Է����ּ���. : ";
            char rech = ' ';
            while (rech != 13) { 
                rech = _getch();
                if (rech == 13) break; // Enter Ű�� ������ �Է� ����
                else if (rech == 8) { // Backspace Ű�� ���
                    if (!new_pw.empty()) { // �Էµ� ���ڰ� ������
                        new_pw.pop_back(); // ������ ���ڸ� ����
                        cout << "\b \b"; // Ŀ�� ��ġ�� �������� �̵����� ������ ����� ��, �ٽ� Ŀ�� ��ġ�� ������� �̵���Ŵ
                    }
                }
                else {
                    new_pw.push_back(rech);
                    cout << '*'; // ��ǥ�� ��ü�Ͽ� ���
                }

            }
            cout << endl;

            if (pw == new_pw) {
                break;
            }
            else {
                cout << "��й�ȣ�� �ٸ��ϴ�." << endl;
                pw.clear();
            }
        }

        cout << ">>�̸� : ";
        cin >> name;
        cout << ">>��ȭ��ȣ : ";
        cin >> phone;
        while (true) {
            cout << ">>������� : ";
            cin >> birth;
            if (birth.length() != 8) {
                cout << "��������� 8�ڸ��� �Է����ּ���." << endl;
                continue;
            }
            break;
        }

        string year = birth.substr(0, 4);
        string month = birth.substr(4, 2);
        string day = birth.substr(6, 2);
        string DATE = year + "-" + month + "-" + day;

        pstmt = con->prepareStatement("INSERT INTO user(id,pw, name, phone, birth) VALUE(?,?, ?, ?, ?)");
        pstmt->setString(1, id);
        pstmt->setString(2, pw);
        pstmt->setString(3, name);
        pstmt->setString(4, phone);
        pstmt->setString(5, DATE);
        pstmt->execute();
        cout << "ȸ�������� �Ϸ�Ǿ����ϴ�." << endl;
        pw.clear();
        Sleep(500);
    }
    string getId() {
        string userId;
        pstmt = con->prepareStatement("SELECT id FROM user WHERE id = ?");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();
        if (result->next()) {
            userId = result->getString(1);
        }
        return userId;
    } 
    void friends() {
        pstmt = con->prepareStatement("SELECT name, status, birth, phone FROM user WHERE id != ?;");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();

        while (result->next()) {
            cout << "-----------------------------" << endl;
            cout << "�̸� : " << result->getString("name") << endl;
            if (result->getString("status") == "") {
                cout << "���¸޼��� : ����" << endl;
            }
            else {
                cout << "���¸޼��� : " << result->getString("status") << endl;
            }
            cout << "���� : " << result->getString("birth") << endl;
            cout << "��ȣ : " << result->getString("phone") << endl;
        }
    }
    void updateStatus()
    {
        cout << ">>���¸޽��� �Է� : ";
        cin.ignore();
        getline(cin, status);
        pstmt = con->prepareStatement("UPDATE user SET status = ? WHERE id = ?");
        pstmt->setString(1, status);
        pstmt->setString(2, id);
        pstmt->executeQuery();
        printf("��������Ʈ �Ǿ����ϴ�.\n");
    }
    void myProfile() {
        pstmt = con->prepareStatement("SELECT name, status, birth, phone FROM user WHERE id = ?;");
        pstmt->setString(1, id);
        result = pstmt->executeQuery();
        while (result->next()) {
            cout << "-----------------------------------------" << endl;
            cout << "�̸� : " << result->getString("name") << endl;
            if (result->getString("status") == "") {
                cout << "���¸޼��� : ����" << endl;
            }
            else {
                cout << "���¸޼��� : " << result->getString("status") << endl;
            }
            cout << "���� : " << result->getString("birth") << endl;
            cout << "��ȣ : " << result->getString("phone") << endl;
            cout << "-----------------------------------------" << endl;
        }
    }
    void search_content_message(){
        string content;
        cout << ">>���� �˻� : ";
        cin >> content;
        pstmt = con->prepareStatement("SELECT chatname, time, message FROM chatting WHERE message LIKE ?");
        pstmt->setString(1, "%" + content + "%");
        result = pstmt->executeQuery();

        if (!result->next()) {
            cout << "�˻� ����� �����ϴ�." << endl;
        }
        else {
            while (true) {
                string chatname = result->getString(1);
                string time = result->getString(2);
                string message = result->getString(3);
                cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
                cout << "������� : " << chatname << " �����ð� : " << time << endl;
                cout << "���� : " << message << endl;
                if (!result->next()) break;
            }
        }
    }
};

int main() {

    SQL sql;
    bool loginSuccess = false;

    while (!loginSuccess) {
        startMenu(); //���� ȭ��
        char startIn = 0;
        cin >> startIn;
        switch (startIn) {
        case '1': //1. �α���
            login();
            if (sql.login() == 1) {
                loginSuccess = true;
                break;
            }
            continue;
        case '2': //2. ���̵� ã��
            searchId();
            sql.searchId();
            continue;
        case '3': //3. ��й�ȣã��
            searchPw();
            sql.searchPw();
            continue;
        case '4': //4. ȸ������
            createUser();
            sql.createUser();
            continue;
        case '0': //0. �ý��� ����
            return -1;
        default: //5 ~ 9. ���Է�
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }

    }

    while (1) {
        mainMenu();
        int mainIn = 0;
        cin >> mainIn;

        if (mainIn == 1) {
            myProfile();
            bool backButton = false;
            while (!backButton) {
                char information = 0;
                cin >> information;
                switch (information) {
                case '1':
                    sql.myProfile();
                    break;
                case '2':
                    sql.updateStatus();
                    continue;
                case '0':
                    backButton = true;
                    break;
                default:
                    cout << "�߸��� �Է��Դϴ�. �ٽ��Է����ּ���" << endl;
                    continue;
                }
            }
        }
        else if (mainIn == 2) {
            friends();
            bool backButton = false;
            while (!backButton) {
                char information = 0;
                cin >> information;
                switch (information) {
                case '1':
                    sql.friends();
                    break;
                case '0':
                    backButton = true;
                    break;
                }
            }
        }

        else if (mainIn == 3) {
            chattinginfo();
            bool backButton = false;
            int code = 0;
            string id;
            while (!backButton) {
                char information = 0;
                cin >> information;
                switch (information) {
                case '1':
                    chattingmain();
                    WSADATA wsa;
                    code = WSAStartup(MAKEWORD(2, 2), &wsa);
                    if (!code) {
                        cout << "ä�ù� ����." << endl;
                        id = sql.getId();
                        client_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
                        // ������ ���� ���� ���� �κ�
                        SOCKADDR_IN client_addr = {};
                        client_addr.sin_family = AF_INET;
                        client_addr.sin_port = htons(7777);
                        InetPton(AF_INET, TEXT("127.0.0.1"), &client_addr.sin_addr);

                        while (1) {
                            if (!connect(client_sock, (SOCKADDR*)&client_addr, sizeof(client_addr))) { // ���� ������ ������ �ش��ϴ� server�� ����!
                                cout << "Server Connect" << endl;
                                send(client_sock,id.c_str(), sizeof(id), 0); 
                                break;
                            }
                            cout << "Connecting..." << endl;
                        }

                        std::thread th2(chat_recv);

                        while (1) {
                            string text;
                            std::getline(cin, text);
                            const char* buffer = text.c_str(); // string���� char* Ÿ������ ��ȯ
                            send(client_sock, buffer, strlen(buffer), 0);
                            if (text == "/����") {
                                closesocket(client_sock);
                                backButton = true;
                                break;
                            }
                        }
                        th2.join();
                        
                    }
                    WSACleanup();
                    break;
                case'2':
                    sql.search_content_message();
                    continue;
                case'0':
                    backButton = true;
                    break;
                default:
                    cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                    continue;
                }
            }
        }

        else if (mainIn == 0) {
            cout << "���α׷��� �����մϴ�." << endl;
            return 0;
        }
        else cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
    }
    return 0;
}