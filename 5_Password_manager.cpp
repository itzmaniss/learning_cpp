#include <iostream>
#include <string>

using namespace std;

class passwordManager {
    public:
        void login() {
            
        }

        string requestPassword(const string account) {
            return getPassword(account);
        }

        void newAccount () {
            // setPassword();
        }

    private:

        bool unlocked = false;


        string generateKey(string password, string key) {
            
            int x = password.size();

            for (int i = 0; ; i++) {
                if (x == i) {
                    i = 0;
                }
                if  (key.size() ==  password.size()) {
                    break;
                }
                key.push_back(key[i]);
            }
            return key;
        }

        string encrypt(const string password, string Account){
            string cipher;

            string key = generateKey(password, Account);
            
            for (int i = 0; i < password.size(); i++) {

                char x = (password[i] + key[i]) % 26;

                x += 'A';

                cipher.push_back(x);
            }

            return cipher;
        }

        string decrypt(const string cipher, const string account) {
            
            string password;
            string key = generateKey(cipher, account);

            for (int i = 0; i < cipher.size(); i++) {

                char x = (cipher[i] - key[i] + 26) % 26;

                x += 'A';

                password.push_back(x);
            }
            return password;
        }

        string getPassword (const string account) {
            
        }

        void setPassword (const string account, const string password, const string username) {

        }

        void unlock () {}
};