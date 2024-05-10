#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>

using namespace std;

vector<string> get_user_input(const vector<string>& symptoms) {
    vector<string> user_symptoms;
    for (const auto& symptom : symptoms) {
        char response;
        cout << "Do you have " << symptom << "? (y/n): ";
        cin >> response;
        if (response == 'y' || response == 'Y') {
            user_symptoms.push_back(symptom);
        }
    }
    return user_symptoms;
}

unordered_map<string, double> get_weighted_symptoms(const vector<string>& user_symptoms, const unordered_map<string, double>& symptoms_weights) {
    unordered_map<string, double> weighted_symptoms;
    for (const auto& symptom : user_symptoms) {
        if (symptoms_weights.find(symptom) != symptoms_weights.end()) {
            weighted_symptoms[symptom] = symptoms_weights.at(symptom);
        }
    }
    return weighted_symptoms;
}

void diagnose_patient() {
    vector<string> symptoms = {"Fever", "Cough", "Headache", "Sore throat", "Shortness of breath", "Chest pain", "Fatigue", "Nausea", "Vomiting", "Dehydration"};

    unordered_map<string, double> symptoms_weights = {
        {"Fever", 1},
        {"Cough", 0.5},
        {"Headache", 0.7},
        {"Sore throat", 0.6},
        {"Shortness of breath", 1.2},
        {"Chest pain", 1.5},
        {"Fatigue", 0.8},
        {"Nausea", 0.7},
        {"Vomiting", 0.9},
        {"Dehydration", 1.3}
    };

    unordered_map<string, vector<string>> diseases = {
        {"Common Cold", {"Fever", "Cough", "Headache", "Sore throat"}},
        {"Flu", {"Fever", "Cough", "Headache"}},
        {"Strep Throat", {"Fever", "Sore throat"}},
        {"Migraine", {"Headache"}},
        {"Pneumonia", {"Fever", "Cough", "Shortness of breath", "Chest pain", "Fatigue", "Confusion", "Nausea", "Vomiting"}}
    };

    vector<string> user_symptoms = get_user_input(symptoms);
    unordered_map<string, double> weighted_symptoms = get_weighted_symptoms(user_symptoms, symptoms_weights);
    unordered_set<string> possible_diseases;

    for (const auto& weighted_symptom : weighted_symptoms) {
        const string& symptom = weighted_symptom.first;
        for (const auto& disease_entry : diseases) {
            const vector<string>& causes = disease_entry.second;
            if (find(causes.begin(), causes.end(), symptom) != causes.end()) {
                possible_diseases.insert(disease_entry.first);
            }
        }
    }

    if (!possible_diseases.empty()) {
        cout << "Possible diseases:" << endl;
        for (const auto& disease_name : possible_diseases) {
            cout << "- " << disease_name << endl;
        }

        // Find the most probable disease based on the weighted sum of symptoms
        string most_probable_disease;
        double max_weighted_sum = 0;
        for (const auto& disease_name : possible_diseases) {
            double weighted_sum = 0;
            const vector<string>& causes = diseases[disease_name];
            for (const auto& symptom : causes) {
                weighted_sum += weighted_symptoms[symptom];
            }
            if (weighted_sum > max_weighted_sum) {
                most_probable_disease = disease_name;
                max_weighted_sum = weighted_sum;
            }
        }

        cout << "\nMost probable disease based on symptoms: " << most_probable_disease << endl;

        // Find recommended doctor for the most probable disease
    } else {
        cout << "No matching diseases found." << endl;
    }
}

int main() {
    diagnose_patient();
    return 0;
}
