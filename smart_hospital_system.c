
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PFILE "patients.dat"
#define DFILE "doctors.dat"
#define AFILE "appointments.dat"
#define DIAGFILE "diagnosis.dat"
#define TFILE "tests.dat"
#define HFILE "history.dat"
#define BFILE "bills.dat"

/* ---------------- STRUCTURES ---------------- */

typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char disease[100];
} Patient;

typedef struct {
    int id;
    char name[50];
    char spec[50];
} Doctor;

typedef struct {
    int pid;
    int did;
    char date[20];
} Appointment;

typedef struct {
    int id;
    int pid;
    int did;
    char symptoms[100];
    char diagnosis[100];
    char prescription[100];
    char date[20];
} Diagnosis;

typedef struct {
    int id;
    int pid;
    char test[100];
    char result[100];
    char remarks[100];
    char date[20];
} TestReport;

typedef struct {
    int pid;
    char diseases[200];
    char surgeries[200];
    char allergies[200];
} History;

typedef struct {
    int pid;
    float amount;
} Bill;

/* ---------------- PATIENT ---------------- */

void addPatient(){
    FILE *fp=fopen(PFILE,"ab");
    Patient p;

    printf("ID: "); scanf("%d",&p.id);
    printf("Name: "); scanf(" %[^\n]",p.name);
    printf("Age: "); scanf("%d",&p.age);
    printf("Gender: "); scanf("%s",p.gender);
    printf("Disease: "); scanf(" %[^\n]",p.disease);

    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    printf("Patient added.\n");
}

void viewPatients(){
    FILE *fp=fopen(PFILE,"rb");
    Patient p;

    printf("\n--- Patients ---\n");
    while(fread(&p,sizeof(p),1,fp)){
        printf("%d | %s | %d | %s | %s\n",
        p.id,p.name,p.age,p.gender,p.disease);
    }
    fclose(fp);
}

void searchPatient(){
    FILE *fp=fopen(PFILE,"rb");
    Patient p;
    int id,found=0;

    printf("Enter ID: ");
    scanf("%d",&id);

    while(fread(&p,sizeof(p),1,fp)){
        if(p.id==id){
            printf("Found: %s (%d)\n",p.name,p.age);
            found=1;
        }
    }
    if(!found) printf("Not found\n");
    fclose(fp);
}

/* ---------------- DOCTOR ---------------- */

void addDoctor(){
    FILE *fp=fopen(DFILE,"ab");
    Doctor d;

    printf("ID: "); scanf("%d",&d.id);
    printf("Name: "); scanf(" %[^\n]",d.name);
    printf("Spec: "); scanf(" %[^\n]",d.spec);

    fwrite(&d,sizeof(d),1,fp);
    fclose(fp);
}

void viewDoctors(){
    FILE *fp=fopen(DFILE,"rb");
    Doctor d;

    printf("\n--- Doctors ---\n");
    while(fread(&d,sizeof(d),1,fp)){
        printf("%d | %s | %s\n",d.id,d.name,d.spec);
    }
    fclose(fp);
}

/* ---------------- APPOINTMENT ---------------- */

void addAppointment(){
    FILE *fp=fopen(AFILE,"ab");
    Appointment a;

    printf("Patient ID: "); scanf("%d",&a.pid);
    printf("Doctor ID: "); scanf("%d",&a.did);
    printf("Date: "); scanf("%s",a.date);

    fwrite(&a,sizeof(a),1,fp);
    fclose(fp);
}

/* ---------------- DIAGNOSIS ---------------- */

void addDiagnosis(){
    FILE *fp=fopen(DIAGFILE,"ab");
    Diagnosis d;

    printf("ID: "); scanf("%d",&d.id);
    printf("Patient ID: "); scanf("%d",&d.pid);
    printf("Doctor ID: "); scanf("%d",&d.did);
    printf("Symptoms: "); scanf(" %[^\n]",d.symptoms);
    printf("Diagnosis: "); scanf(" %[^\n]",d.diagnosis);
    printf("Prescription: "); scanf(" %[^\n]",d.prescription);
    printf("Date: "); scanf("%s",d.date);

    fwrite(&d,sizeof(d),1,fp);
    fclose(fp);
}

/* ---------------- TEST REPORT ---------------- */

void addTest(){
    FILE *fp=fopen(TFILE,"ab");
    TestReport t;

    printf("ID: "); scanf("%d",&t.id);
    printf("Patient ID: "); scanf("%d",&t.pid);
    printf("Test: "); scanf(" %[^\n]",t.test);
    printf("Result: "); scanf(" %[^\n]",t.result);
    printf("Remarks: "); scanf(" %[^\n]",t.remarks);
    printf("Date: "); scanf("%s",t.date);

    fwrite(&t,sizeof(t),1,fp);
    fclose(fp);
}

/* ---------------- HISTORY ---------------- */

void addHistory(){
    FILE *fp=fopen(HFILE,"ab");
    History h;

    printf("Patient ID: "); scanf("%d",&h.pid);
    printf("Diseases: "); scanf(" %[^\n]",h.diseases);
    printf("Surgeries: "); scanf(" %[^\n]",h.surgeries);
    printf("Allergies: "); scanf(" %[^\n]",h.allergies);

    fwrite(&h,sizeof(h),1,fp);
    fclose(fp);
}

/* ---------------- BILL ---------------- */

void addBill(){
    FILE *fp=fopen(BFILE,"ab");
    Bill b;

    printf("Patient ID: "); scanf("%d",&b.pid);
    printf("Amount: "); scanf("%f",&b.amount);

    fwrite(&b,sizeof(b),1,fp);
    fclose(fp);
}

/* ---------------- COMPLETE HISTORY ---------------- */

void fullHistory(){
    int id;
    printf("Enter Patient ID: ");
    scanf("%d",&id);

    Patient p;
    FILE *fp=fopen(PFILE,"rb");

    printf("\n=== HISTORY ===\n");

    while(fread(&p,sizeof(p),1,fp)){
        if(p.id==id){
            printf("Patient: %s\n",p.name);
            printf("Disease: %s\n",p.disease);
        }
    }
    fclose(fp);

    Diagnosis d;
    fp=fopen(DIAGFILE,"rb");
    printf("\n--- Diagnosis ---\n");
    while(fread(&d,sizeof(d),1,fp)){
        if(d.pid==id)
            printf("%s | %s | %s\n",d.symptoms,d.diagnosis,d.prescription);
    }
    fclose(fp);

    TestReport t;
    fp=fopen(TFILE,"rb");
    printf("\n--- Tests ---\n");
    while(fread(&t,sizeof(t),1,fp)){
        if(t.pid==id)
            printf("%s | %s\n",t.test,t.result);
    }
    fclose(fp);
}

/* ---------------- MAIN MENU ---------------- */

int main(){
    int c;

    while(1){
        printf("\n===========================\n");
        printf(" SMART HOSPITAL SYSTEM\n");
        printf("===========================\n");

        printf("1.Add Patient\n2.View Patients\n3.Search Patient\n");
        printf("4.Add Doctor\n5.View Doctors\n");
        printf("6.Add Appointment\n");
        printf("7.Add Diagnosis\n8.Add Test\n9.Add History\n");
        printf("10.Add Bill\n11.Full History\n0.Exit\n");
        printf("Choice: ");

        scanf("%d",&c);

        switch(c){
            case 1:addPatient();break;
            case 2:viewPatients();break;
            case 3:searchPatient();break;
            case 4:addDoctor();break;
            case 5:viewDoctors();break;
            case 6:addAppointment();break;
            case 7:addDiagnosis();break;
            case 8:addTest();break;
            case 9:addHistory();break;
            case 10:addBill();break;
            case 11:fullHistory();break;
            case 0:exit(0);
            default:printf("Invalid\n");
        }
    }
}
