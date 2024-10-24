object FMijanka: TFMijanka
  Left = 192
  Top = 107
  BorderStyle = bsDialog
  Caption = 'Pozwolenie zaj'#281'cia odcinka'
  ClientHeight = 354
  ClientWidth = 597
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnPaint = FormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object PBMijanka: TPaintBox
    Left = 0
    Top = 41
    Width = 597
    Height = 211
    Align = alClient
  end
  object Panel1: TPanel
    Left = 0
    Top = 293
    Width = 597
    Height = 61
    Align = alBottom
    TabOrder = 0
    object Label1: TLabel
      Left = 264
      Top = 25
      Width = 47
      Height = 20
      Caption = 'minut'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BZezwalam: TButton
      Left = 24
      Top = 20
      Width = 75
      Height = 25
      Caption = 'Zezwalam'
      ModalResult = 1
      TabOrder = 0
      OnClick = BZezwalamClick
    end
    object BCzekaj: TButton
      Left = 128
      Top = 20
      Width = 75
      Height = 25
      Caption = 'Czekaj'
      ModalResult = 1
      TabOrder = 1
      OnClick = BCzekajClick
    end
    object ECzekaj: TEdit
      Left = 216
      Top = 17
      Width = 33
      Height = 28
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      MaxLength = 2
      ParentFont = False
      TabOrder = 2
      Text = '1'
    end
  end
  object PNapis: TPanel
    Left = 0
    Top = 252
    Width = 597
    Height = 41
    Align = alBottom
    TabOrder = 1
    object LTekst: TLabel
      Left = 19
      Top = 16
      Width = 3
      Height = 13
    end
  end
  object PTytul: TPanel
    Left = 0
    Top = 0
    Width = 597
    Height = 41
    Align = alTop
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
  end
end
