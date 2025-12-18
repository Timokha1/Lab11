object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 689
  ClientWidth = 910
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object GroupBox1: TGroupBox
    Left = 24
    Top = 32
    Width = 521
    Height = 177
    Caption = #1052#1072#1090#1077#1084#1072#1090#1080#1095#1085#1072#1084#1086#1076#1077#1083#1100
    TabOrder = 0
    object Edit1: TEdit
      Left = 368
      Top = 24
      Width = 121
      Height = 23
      TabOrder = 0
      Text = '5'
    end
    object Edit2: TEdit
      Left = 368
      Top = 64
      Width = 121
      Height = 23
      TabOrder = 1
      Text = 'x*x + y'
    end
    object EditY: TEdit
      Left = 368
      Top = 112
      Width = 121
      Height = 23
      TabOrder = 2
      Text = '10'
    end
  end
  object GroupBox2: TGroupBox
    Left = 24
    Top = 232
    Width = 521
    Height = 201
    Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1080
    TabOrder = 1
    object Edit3: TEdit
      Left = 368
      Top = 16
      Width = 121
      Height = 23
      TabOrder = 0
    end
    object Edit4: TEdit
      Left = 368
      Top = 53
      Width = 121
      Height = 23
      TabOrder = 1
    end
    object Edit5: TEdit
      Left = 368
      Top = 98
      Width = 121
      Height = 23
      TabOrder = 2
    end
    object Edit6: TEdit
      Left = 368
      Top = 136
      Width = 121
      Height = 23
      TabOrder = 3
    end
    object Edit7: TEdit
      Left = 368
      Top = 175
      Width = 121
      Height = 23
      TabOrder = 4
    end
  end
  object GroupBox3: TGroupBox
    Left = 24
    Top = 456
    Width = 521
    Height = 49
    Caption = #1047#1085#1072#1082#1080' '#1087#1110#1089#1083#1103' '#1082#1088#1072#1087#1082#1080
    TabOrder = 2
    object ComboBox1: TComboBox
      Left = 32
      Top = 24
      Width = 41
      Height = 23
      TabOrder = 0
      Text = '2'
      OnChange = ComboBox1Change
    end
  end
  object Button1: TButton
    Left = 688
    Top = 326
    Width = 97
    Height = 65
    Caption = #1054#1073#1095#1080#1089#1083#1080#1090#1080
    TabOrder = 3
    OnClick = Button1Click
  end
  object Memo1: TMemo
    Left = 600
    Top = 56
    Width = 257
    Height = 183
    TabOrder = 4
  end
  object Button2: TButton
    Left = 688
    Top = 407
    Width = 97
    Height = 61
    Caption = #1042#1080#1081#1090#1080
    TabOrder = 5
    OnClick = Button2Click
  end
end
