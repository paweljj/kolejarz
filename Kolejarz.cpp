//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Kolejarz.res");
USEFORM("FKolejarz.cpp", FGlowna);
USEFORM("Opcje.cpp", FOpcje);
USEFORM("OProgramie.cpp", FOProgramie);
USEUNIT("Inne.cpp");
USEUNIT("Stacja.cpp");
USEUNIT("Rozklad.cpp");
USEUNIT("Obiekt.cpp");
USEFORM("ORozklad.cpp", FRozklad);
USEFORM("OBocznica.cpp", FBocznica);
USEUNIT("Lokom.cpp");
USEFORM("OLokom.cpp", FLokomot);
USEFORM("Podglad.cpp", FPodgladSkladu);
USEFORM("Poczatek.cpp", FPoczatek);
USEFORM("Uwagi.cpp", FUwagi);
USEFORM("OMijanka.cpp", FMijanka);
USEFORM("WjazdWyjazd.cpp", FWjazdWyjazd);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Kolejarz";
                 Application->HelpFile = "";
                 Application->CreateForm(__classid(TFGlowna), &FGlowna);
                 Application->CreateForm(__classid(TFOpcje), &FOpcje);
                 Application->CreateForm(__classid(TFOProgramie), &FOProgramie);
                 Application->CreateForm(__classid(TFRozklad), &FRozklad);
                 Application->CreateForm(__classid(TFBocznica), &FBocznica);
                 Application->CreateForm(__classid(TFLokomot), &FLokomot);
                 Application->CreateForm(__classid(TFPodgladSkladu), &FPodgladSkladu);
                 Application->CreateForm(__classid(TFPoczatek), &FPoczatek);
                 Application->CreateForm(__classid(TFUwagi), &FUwagi);
                 Application->CreateForm(__classid(TFMijanka), &FMijanka);
                 Application->CreateForm(__classid(TFWjazdWyjazd), &FWjazdWyjazd);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
