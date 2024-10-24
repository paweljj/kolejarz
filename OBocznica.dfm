object FBocznica: TFBocznica
  Left = 181
  Top = 17
  Width = 544
  Height = 375
  Caption = 'Tory postojowe'
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnActivate = FormActivate
  OnCloseQuery = FormCloseQuery
  OnDestroy = FormDestroy
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PBBocznica: TPaintBox
    Left = 0
    Top = 0
    Width = 536
    Height = 289
    Align = alClient
    Color = clWhite
    ParentColor = False
    OnMouseDown = PBBocznicaMouseDown
    OnMouseMove = PBBocznicaMouseMove
    OnPaint = PBBocznicaPaint
  end
  object Panel1: TPanel
    Left = 0
    Top = 289
    Width = 536
    Height = 52
    Align = alBottom
    TabOrder = 0
    OnMouseMove = Panel1MouseMove
    object BOK: TButton
      Left = 231
      Top = 13
      Width = 75
      Height = 25
      Caption = 'Zamknij'
      ModalResult = 1
      TabOrder = 0
      OnMouseMove = BOKMouseMove
    end
  end
end
