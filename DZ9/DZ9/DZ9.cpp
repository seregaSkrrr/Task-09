#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Serializer {
public:
    virtual ~Serializer() {}
    virtual void BeginArray() = 0;
    virtual void AddArrayItem(const string&) = 0;
    virtual void EndArray() = 0;
};

class JsonSerializer : public Serializer {
public:
    void BeginArray() override {
        Output.push_back('[');
        Depth++;
    }

    void AddArrayItem(const string& item) override {
        if (!Output.empty() && Output.back() != '[') {
            Output.push_back(',');
        }
        Output.push_back('"');
        Output.append(item);
        Output.push_back('"');
    }

    void EndArray() override {
        Output.push_back(']');
        Depth--;
        if (Depth == 0) {
            cout << Output << endl;
            Output.clear();
        }
    }

private:
    string Output;
    int Depth = 0;
};

int main() {
    JsonSerializer serializer;

    serializer.BeginArray();
    serializer.EndArray();

    serializer.BeginArray();
    serializer.AddArrayItem("string");
    serializer.EndArray();

    serializer.BeginArray();
    serializer.AddArrayItem("first");
    serializer.AddArrayItem("second");
    serializer.EndArray();

    serializer.BeginArray();
    serializer.BeginArray();
    serializer.EndArray();
    serializer.EndArray();

    return 0;
}