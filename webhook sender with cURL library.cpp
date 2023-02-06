#include <iostream>
#include <string>
#include <curl/curl.h>
using namespace std;

size_t writeCallback(char* buf, size_t size, size_t nmemb, void* up) {
    for (int c = 0; c < size * nmemb; c++) {
        std::cout << buf[c];
    }
    return size * nmemb;
}

int main(void) {
    cout << "type the webhook: ";
        string webhook;
    cin >> webhook;
    cin.get();
    cout << "\ntext: ";
        char caca[501];
        cin.getline(caca, 501);
        std::string payload = "{\"content\": \"";
        payload += caca;
        payload += "\"}";
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL,webhook );
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());
        curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type:application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &writeCallback);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}
