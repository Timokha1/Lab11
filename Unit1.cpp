//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include <cmath>
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
//Telement
class Telement
{
protected:
    Telement *left, *right;
public:
    Telement(Telement* L = nullptr, Telement* R = nullptr) : left(L), right(R) {}
    virtual ~Telement(void) { delete left; delete right; }

    virtual double rezult(double x = 0, double y = 0) = 0;
    virtual Telement* copy(void) = 0;
    virtual Telement* differX(void) = 0;
    virtual Telement* differY(void) = 0;
    virtual AnsiString to_string() = 0;
};

//---------------------------------------------------------------------------
//real
class Real : public Telement
{
    double f;
public:
	Real(double F) : Telement(nullptr, nullptr), f(F) {}

    double rezult(double x = 0, double y = 0) override { return f; }
    Telement* copy(void) override { return new Real(f); }
    Telement* differX(void) override { return new Real(0); }
    Telement* differY(void) override { return new Real(0); }
    AnsiString to_string() override { return FloatToStr(f); }
};

//varx
class VarX : public Telement
{
public:
	VarX() : Telement(nullptr, nullptr) {}

    double rezult(double x = 0, double y = 0) override { return x; }
    Telement* copy(void) override { return new VarX(); }
    Telement* differX(void) override { return new Real(1); }
    Telement* differY(void) override { return new Real(0); }
    AnsiString to_string() override { return "x"; }
};

//vary
class VarY : public Telement
{
public:
	VarY() : Telement(nullptr, nullptr) {}

    double rezult(double x = 0, double y = 0) override { return y; }
    Telement* copy(void) override { return new VarY(); }
    Telement* differX(void) override { return new Real(0); }
    Telement* differY(void) override { return new Real(1); }
    AnsiString to_string() override { return "y"; }
};

//plus
class Plus : public Telement
{
public:
	Plus(Telement* L, Telement* R) : Telement(L, R) {}

    double rezult(double x = 0, double y = 0) override { return left->rezult(x,y) + right->rezult(x,y); }
    Telement* copy(void) override { return new Plus(left->copy(), right->copy()); }
    Telement* differX(void) override { return new Plus(left->differX(), right->differX()); }
    Telement* differY(void) override { return new Plus(left->differY(), right->differY()); }
    AnsiString to_string() override { return "(" + left->to_string() + " + " + right->to_string() + ")"; }
};

//minus
class Minus : public Telement
{
public:
	Minus(Telement* L, Telement* R) : Telement(L, R) {}

    double rezult(double x = 0, double y = 0) override { return left->rezult(x,y) - right->rezult(x,y); }
    Telement* copy(void) override { return new Minus(left->copy(), right->copy()); }
    Telement* differX(void) override { return new Minus(left->differX(), right->differX()); }
    Telement* differY(void) override { return new Minus(left->differY(), right->differY()); }
    AnsiString to_string() override { return "(" + left->to_string() + " - " + right->to_string() + ")"; }
};

//mult
class Mult : public Telement
{
public:
	Mult(Telement* L, Telement* R) : Telement(L, R) {}

    double rezult(double x = 0, double y = 0) override { return left->rezult(x,y) * right->rezult(x,y); }
    Telement* copy(void) override { return new Mult(left->copy(), right->copy()); }
    Telement* differX(void) override
    {
        return new Plus(new Mult(left->differX(), right->copy()), new Mult(left->copy(), right->differX()));
    }
    Telement* differY(void) override
    {
        return new Plus(new Mult(left->differY(), right->copy()), new Mult(left->copy(), right->differY()));
    }
    AnsiString to_string() override { return "(" + left->to_string() + " * " + right->to_string() + ")"; }
};

//div
class Div : public Telement
{
public:
	Div(Telement* L, Telement* R) : Telement(L, R) {}

    double rezult(double x = 0, double y = 0) override { return left->rezult(x,y)/right->rezult(x,y); }
    Telement* copy(void) override { return new Div(left->copy(), right->copy()); }
    Telement* differX(void) override
    {
        return new Div(new Minus(new Mult(left->differX(), right->copy()), new Mult(left->copy(), right->differX())), new Mult(right->copy(), right->copy()));
    }
    Telement* differY(void) override
    {
        return new Div(new Minus(new Mult(left->differY(), right->copy()), new Mult(left->copy(), right->differY())), new Mult(right->copy(), right->copy()));
    }
    AnsiString to_string() override { return "(" + left->to_string() + " / " + right->to_string() + ")"; }
};


//Sin Cos
class MySin;

class MyCos : public Telement
{
public:
	MyCos(Telement* L) : Telement(L, nullptr) {}

    double rezult(double x = 0, double y = 0) override { return cos(left->rezult(x,y)); }
    Telement* copy(void) override { return new MyCos(left->copy()); }
	Telement* differX(void) override;
	Telement* differY(void) override;
	AnsiString to_string() override { return "cos(" + left->to_string() + ")"; }
};

//mysin
class MySin : public Telement
{
public:
	MySin(Telement* L) : Telement(L, nullptr) {}

    double rezult(double x = 0, double y = 0) override { return sin(left->rezult(x,y)); }
	Telement* copy(void) override { return new MySin(left->copy()); }
	Telement* differX(void) override;
	Telement* differY(void) override;
    AnsiString to_string() override { return "sin(" + left->to_string() + ")"; }
};

Telement* MyCos::differX(void) { return new Mult(new Mult(new Real(-1), new MySin(left->copy())), left->differX()); }
Telement* MyCos::differY(void) { return new Mult(new Mult(new Real(-1), new MySin(left->copy())), left->differY()); }

Telement* MySin::differX(void) { return new Mult(new MyCos(left->copy()), left->differX()); }
Telement* MySin::differY(void) { return new Mult(new MyCos(left->copy()), left->differY()); }

//---------------------------------------------------------------------------

// PosFromEnd fuction
int PosFromEnd(AnsiString s, AnsiString sub)
{
    int l = s.Length();
    AnsiString p; p.SetLength(l);
    for(int i=1;i<=l;i++) p[l-i+1] = s[i];
    if(p.Pos(sub)>0) return l - p.Pos(sub) + 1;
    return 0;
}

//form
Telement* form(AnsiString s)
{
    s = s.Trim();
    int l = s.Length();
    int p;
    AnsiString s1, s2;

    if ((p = PosFromEnd(s, "+")) > 1) { s1=s.SubString(1,p-1); s2=s.SubString(p+1,l-p); return new Plus(form(s1), form(s2)); }
    if ((p = PosFromEnd(s, "-")) > 1) { s1=s.SubString(1,p-1); s2=s.SubString(p+1,l-p); return new Minus(form(s1), form(s2)); }
    if ((p = PosFromEnd(s, "*")) > 1) { s1=s.SubString(1,p-1); s2=s.SubString(p+1,l-p); return new Mult(form(s1), form(s2)); }
    if ((p = PosFromEnd(s, "/")) > 1) { s1=s.SubString(1,p-1); s2=s.SubString(p+1,l-p); return new Div(form(s1), form(s2)); }

    if(s.Pos("sin(")==1 && s[s.Length()]==')') return new MySin(form(s.SubString(5, s.Length()-5)));
    if(s.Pos("cos(")==1 && s[s.Length()]==')') return new MyCos(form(s.SubString(5, s.Length()-5)));

    if(s=="x") return new VarX();
    if(s=="y") return new VarY();
    try { return new Real(StrToFloat(s)); } catch(...) { return new Real(0); }
}

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner) {}

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    try {
        double X = StrToFloat(Edit1->Text);
        double Y = StrToFloat(EditY->Text);

        Telement* f  = form(Edit2->Text);

        Telement* f1 = f->differX();
        Telement* f2 = f1->differX();
        Telement* f3 = f2->differX();

        int precision = 15;
        int digits = StrToInt(ComboBox1->Text);

        Edit3->Text = FloatToStrF(X, ffFixed, precision, digits);
        Edit4->Text = FloatToStrF(f->rezult(X,Y), ffFixed, precision, digits);
        Edit5->Text = FloatToStrF(f1->rezult(X,Y), ffFixed, precision, digits);
        Edit6->Text = FloatToStrF(f2->rezult(X,Y), ffFixed, precision, digits);
        Edit7->Text = FloatToStrF(f3->rezult(X,Y), ffFixed, precision, digits);

        Memo1->Text = f->to_string();

        delete f; delete f1; delete f2; delete f3;
	} catch (...)
	{
		ShowMessage("Помилка");
	}
}

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
    Button1Click(Button1);
}
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    exit(1);
}
