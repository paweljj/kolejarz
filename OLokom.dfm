object FLokomot: TFLokomot
  Left = 193
  Top = 92
  Width = 444
  Height = 394
  Caption = 'Lokomotywownia'
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object PBLoki: TPaintBox
    Left = 0
    Top = 0
    Width = 436
    Height = 308
    Align = alClient
    OnMouseDown = PBLokiMouseDown
    OnPaint = PBLokiPaint
  end
  object Panel1: TPanel
    Left = 0
    Top = 308
    Width = 436
    Height = 52
    Align = alBottom
    TabOrder = 0
    object BZamknij: TButton
      Left = 180
      Top = 14
      Width = 75
      Height = 25
      Caption = 'Zamknij'
      ModalResult = 1
      TabOrder = 0
    end
  end
  object LBSzopy: TListBox
    Left = 0
    Top = 8
    Width = 110
    Height = 55
    ExtendedSelect = False
    ItemHeight = 13
    TabOrder = 1
    Visible = False
    OnClick = LBSzopyClick
  end
end
