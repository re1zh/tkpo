#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <fstream>
#include <sstream>

using namespace std;

string ComputeHash(const string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)input.c_str(), input.size(), hash);

    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

class XMLDocument {
    public:
        string xml_content;
        void Show() const {
            cout << xml_content << endl;
        }
};

class Builder {
public:
    virtual ~Builder() {}
    virtual void Reset() = 0;
    virtual void SetHeader(const string& title) = 0;
    virtual void SetAuthors(const vector<string>& authors) = 0;
    virtual void SetBody(const string& text) = 0;
    virtual void SetHash(const string& hash, bool valid) = 0;
    virtual XMLDocument* GetResult() = 0;
};

class ConcreteBuilder : public Builder {
public:
    ConcreteBuilder() : document(new XMLDocument()) {}
    ~ConcreteBuilder() {
        delete document;
    }
    void Reset() override {
        document = new XMLDocument();
    }
    void SetHeader(const string& title) override {
        document->xml_content += "<article>\n  <title>" + title + "</title>\n";
    }
    void SetAuthors(const vector<string>& authors) override {
        document->xml_content += "  <authors>\n";
        for (const auto& author : authors) {
            document->xml_content += "    <author>" + author + "</author>\n";
        }
        document->xml_content += "  </authors>\n";
    }
    void SetBody(const string& text) override {
        document->xml_content += "  <body>" + text + "</body>\n";
    }
    void SetHash(const string& hash, bool valid) override {
        document->xml_content += "  <hash valid=\"" + string(valid ? "true" : "false") + "\">" + hash + "</hash>\n";
        document->xml_content += "</article>";
    }
    XMLDocument* GetResult() override {
        XMLDocument* result = document;
        Reset();
        return result;
    }
    private:
        XMLDocument* document;
};

class Director {
public:
    void SetBuilder(Builder* b) {
        builder = b;
    }

    void Construct(const string& title, const vector<string>& authors, const string& text, const string& hash) {
        builder->Reset();
        builder->SetHeader(title);
        builder->SetAuthors(authors);
        builder->SetBody(text);

        string computed_hash = ComputeHash(text);
        cout << "Сгенерированный HASH: " << computed_hash << endl;
        cout << "Изначальный HASH: " << hash << endl;
        bool valid = (computed_hash == hash);
        builder->SetHash(hash, valid);
    }
    private:
        Builder* builder;
};

bool ReadArticle(const string& filename, string& title, vector<string>& authors, string& body, string& hash) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка! Невозможно открыть файл " << filename << endl;
        return false;
    }

    getline(file, title);

    string authors_line;
    getline(file, authors_line);
    stringstream ss(authors_line);
    string author;
    while (getline(ss, author, ',')) {
        authors.push_back(author);
    }

    string line;
    while (getline(file, line)) {
        if (file.eof()) {
            hash = line;
        } else {
            body += line + "\n";
        }
    }
    file.close();
    return true;
}

int main() {
    const string input_filename = "/Users/re1zh/Desktop/mospolytech/tkpo/lab3/Builder/article.txt";
    const string output_filename = "/Users/re1zh/Desktop/mospolytech/tkpo/lab3/Builder/article.xml";

    string title, body, hash;
    vector<string> authors;

    if (!ReadArticle(input_filename, title, authors, body, hash)) {
        return 1;
    }

    // cout << "Title: " << title << endl;
    // cout << "Authors: ";
    // for (const auto& author : authors) {
    //     cout << author << ", ";
    // }
    // cout << endl;
    // cout << "Body: " << body << endl;
    // cout << "Hash: " << hash << endl;

    ConcreteBuilder builder;
    Director director;
    director.SetBuilder(&builder);

    director.Construct(title, authors, body, hash);

    XMLDocument* xmlDoc = builder.GetResult();
    if (xmlDoc == nullptr) {
        cerr << "Ошибка! Невозможно создать XML" << endl;
        return 1;
    }

    ofstream output_file(output_filename);
    if (!output_file.is_open()) {
        cerr << "Ошибка! Невозможно открыть файл для записи " << output_filename << endl;
        return 1;
    }

    output_file << xmlDoc->xml_content;
    output_file.close();

    if (output_file.fail()) {
        cerr << "Ошибка! Невозможно сделать запись в файл " << output_filename << endl;
        return 1;
    }

    cout << "XML Document: " << output_filename << endl;

    delete xmlDoc;

    return 0;
}
