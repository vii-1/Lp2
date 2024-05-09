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
    vector<string> symptoms = {"Fever", "Cough", "Headache", "Sore throat", "Shortness of breath", "Chest pain", "Fatigue", "Nausea", "Vomiting", "Dehydration", "Increased thirst", "Blurred vision", "Weight loss", "Abdominal Cramps"};

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
        {"Dehydration", 1.3},
        {"Increased thirst", 0.8},
        {"Blurred vision", 1.1},
        {"Weight loss", 1.4},
        {"Abdominal Cramps", 0.9}
    };

    unordered_map<string, vector<string>> diseases = {
        {"Common Cold", {"Fever", "Cough", "Headache", "Sore throat"}},
        {"Flu", {"Fever", "Cough", "Headache"}},
        {"Strep Throat", {"Fever", "Sore throat"}},
        {"Migraine", {"Headache"}},
        {"Pneumonia", {"Fever", "Cough", "Shortness of breath", "Chest pain", "Fatigue", "Confusion", "Nausea", "Vomiting"}},
        {"Gastroenteritis", {"Diarrhea", "Nausea", "Vomiting", "Abdominal cramps", "Fever", "Blood in stool", "Dehydration"}},
        {"Diabetes", {"Increased thirst", "Frequent urination", "Extreme hunger", "Unexplained weight loss", "Fatigue", "Irritability", "Blurred vision", "Slow-healing sores"}},
        {"Hypertension", {"Headaches", "Shortness of breath", "Nosebleeds", "Dizziness", "Chest pain", "Vision changes"}},
        {"Otitis Media (Ear Infection)", {"Ear pain", "Tugging or pulling at the ear", "Difficulty sleeping", "Fussiness in infants and young children", "Fever", "Fluid drainage from the ear"}},
        {"Meningitis", {"Sudden high fever", "Stiff neck", "Severe headache", "Headache with nausea or vomiting", "Confusion or difficulty concentrating", "Seizures", "Sleepiness or difficulty waking up", "Sensitivity to light"}},
        {"Hyperthyroidism", {"Weight loss", "Rapid heartbeat (tachycardia)", "Irregular heartbeat (arrhythmia)", "Increased appetite", "Nervousness", "Anxiety", "Irritability", "Tremor (shaking) in hands and fingers", "Sweating"}}
    };

    unordered_map<string, vector<string>> doctor_recommendations = {
        {"General Practitioner (GP)", {"Common Cold", "Flu", "Strep Throat", "Pneumonia", "Urinary Tract Infection (UTI)", "Gastroenteritis", "Hypertension", "Otitis Media (Ear Infection)"}},
        {"Pulmonologist", {"Pneumonia"}},
        {"Gastroenterologist", {"Gastroenteritis"}},
        {"Endocrinologist", {"Diabetes", "Hyperthyroidism"}},
        {"Neurologist", {"Migraine", "Meningitis"}},
        {"ENT Specialist", {"Strep Throat", "Otitis Media (Ear Infection)"}},
        {"Cardiologist", {"Hypertension"}}
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
        cout << "\nRecommended doctor(s) to consult for the most probable disease:" << endl;
        for (const auto& doctor_entry : doctor_recommendations) {
            const vector<string>& specialties = doctor_entry.second;
            if (find(specialties.begin(), specialties.end(), most_probable_disease) != specialties.end()) {
                cout << "- " << doctor_entry.first << endl;
            }
        }
    } else {
        cout << "No matching diseases found." << endl;
    }
}

int main() {
    diagnose_patient();
    return 0;
}
