#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <cfloat>
using namespace System;
using namespace System::Windows::Forms;
public ref class SFigure abstract
{
protected:
    double a;
    double x;
    double y;
    double z;
public:
    SFigure(double p1, double p2, double p3, double p4) {
        a = p1;
        x = p2;
        y = p3;
        z = p4;

    }
    SFigure() {
        a = 0;
    }
    virtual double Volume() = 0;

};

ref class Sphere : public SFigure
{
private:
    double r;
    double x;
    double y;
    double z;
public:
    Sphere(double p1, double p2, double p3, double p4) : SFigure(p1, p2, p3, p4) {
        x = p2;
        y = p3;
        z = p4;
        if (p1 < 0 )
            throw gcnew System::Exception("Error: The radius length cannot be negative.");
        else
            r = p1;
    }

    Sphere() : SFigure(0,0,0,0),  r (1){}  

    double Volume() override {
        return (4.0 / 3.0) * M_PI * r * r * r;
    }

    virtual String^ ToString() override {  
        return "Sphere: coordinates of the center - " + "(" + Convert::ToString(x) +", " 
            + Convert::ToString(y) + ", " + Convert::ToString(z) +
            "), radius = " + Convert::ToString(r) + ", Volume = " + Convert::ToString(Volume());
    }
};
ref class Cylinder : public SFigure
{
private:
    double a;
    double r;
    double x;
    double y;
    double z;
public:
    Cylinder(double p1, double p2, double p3, double p4, double p5) : SFigure(p1, p2, p3, p4) {
        x = p2;
        y = p3;
        z = p4;
        if (p1 < 0 || p2 <0)
            throw gcnew System::Exception("Error: The radius and side length cannot be negative.");
        else
            a = p1;
            r = p2;
    }

    Cylinder() : SFigure(0,0,0,0), r(1) , a (1) {}

    double Volume() override {
        return M_PI * r * r * a;
    }

    virtual String^ ToString() override {
        return "Cylinder: coordinates of the center - " + "(" + Convert::ToString(x) + ", "
            + Convert::ToString(y) + ", " + Convert::ToString(z) + "), radius = " + Convert::ToString(r) 
+ ", high = " + Convert::ToString(a) + ", Volume = " + Convert::ToString(Volume());
    }
};
ref class Cub : public SFigure
{
private:
    double a;
    double x;
    double y;
    double z;
public:
    Cub(double p1, double p2, double p3, double p4) : SFigure(p1, p2, p3, p4) {
        x = p2;
        y = p3;
        z = p4;
        if (p1 < 0)
            throw gcnew System::Exception("Error: The side length cannot be negative.");
        else
            a = p1;
    }

    Cub() : SFigure(0,0,0,0), a(1) {}  

    double Volume() override {
        return a * a * a;
    }

    virtual String^ ToString() override {  
        return "Cube: coordinates of the center - " + "(" + Convert::ToString(x) + ", " 
            + Convert::ToString(y) + ", " + Convert::ToString(z)
            + "), side a = " + Convert::ToString(a) + ", Volume = " + Convert::ToString(Volume());
    }
};
ref class Cont {
    ref class Elem {
    public:
        SFigure^ ptrS;
        Elem^ next;
    };
private:
    Elem^ first;
    TextBox^ tBox;

public:
    Cont(TextBox^ p1) {
        tBox = p1;
   
        first = nullptr;
    }
    void Add(SFigure^ s) {
        Elem^ temp = gcnew Elem;
        temp->ptrS = s;
        temp->next = first;
        first = temp;
    }
  
    void Output()
    {
        Elem^ temp = first;
        tBox->Text = "List of figures: ";
        while (temp != nullptr) {
            tBox->Text += "\r\n" + temp->ptrS->ToString();
            temp = temp->next;
            if (temp)tBox->Text += ";";
           
        }
        FindMinVolume();
    }
    void FindMinVolume() {
        Elem^ temp = first;
        double minVolume = DBL_MAX;
        SFigure^ minFigure = nullptr;

        while (temp != nullptr) {
            double volume = temp->ptrS->Volume();
            if (volume < minVolume) {
                minVolume = volume;
                minFigure = temp->ptrS;
            }
            temp = temp->next;
        }

        if (minFigure != nullptr) {
            tBox->Text += "\r\n\r\nFigure with min volume: " + minFigure->ToString();
        }
        else {
            tBox->Text += "\r\n\r\nNo figures in the list";
        }
    }
};
    



