#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

// Function to write received data to file
size_t writeDataCallback(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    return fwrite(ptr, size, nmemb, stream);
}

// Function to send data to Discord webhook
void sendToDiscord(const string& webhook, const string& message) {
    CURL* curl;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, webhook.c_str());

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        string payload = "{\"content\": \"" + message + "\"}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload.c_str());

        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

// Function to download videos
bool downloadVideo(const string& videoUrl, const string& fileName, const string& webhook) {
    FILE* fp;
    CURL* curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        if (fopen_s(&fp, fileName.c_str(), "wb") == 0) {
            curl_easy_setopt(curl, CURLOPT_URL, videoUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeDataCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            fclose(fp); // Close the file after writing
        }
        else {
            cout << "Error opening file for writing" << endl;
            res = CURLE_WRITE_ERROR;
        }

        curl_easy_cleanup(curl);
    }

    return res == CURLE_OK;
}

int main() {
    string filename;
    cout << "Enter the filename containing video URLs: ";
    cin >> filename;

    string webhook;
    cout << "Enter the Discord webhook: ";
    cin >> webhook;

    ifstream file(filename);
    if (file.is_open()) {
        string url;
        int count = 1;
        while (getline(file, url)) {
            string fileName = "video_" + to_string(count) + ".mp4"; // Name for the downloaded file
            bool success = downloadVideo(url, fileName, webhook);
            if (success) {
                cout << "Downloaded: " << url << " -> " << fileName << endl;
            }
            else {
                cout << "Failed to download: " << url << endl;
            }
            count++;
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }

    return 0;
}
