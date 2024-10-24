object FPodgladSkladu: TFPodgladSkladu
  Left = 0
  Top = 409
  VertScrollBar.Visible = False
  AutoScroll = False
  BorderIcons = [biSystemMenu]
  ClientHeight = 65
  ClientWidth = 790
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object SBTlo: TScrollBox
    Left = 0
    Top = 0
    Width = 790
    Height = 65
    HorzScrollBar.Tracking = True
    VertScrollBar.Visible = False
    Align = alTop
    TabOrder = 0
    object IPodglad: TImage
      Left = 8
      Top = 0
      Width = 777
      Height = 40
    end
  end
end
