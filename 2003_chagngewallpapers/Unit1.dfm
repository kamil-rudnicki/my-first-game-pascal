object Tapeter: TTapeter
  Left = 254
  Top = 133
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Tapeter'
  ClientHeight = 321
  ClientWidth = 441
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Informacje: TPageControl
    Left = 0
    Top = 0
    Width = 441
    Height = 321
    ActivePage = TabSheet1
    TabIndex = 0
    TabOrder = 0
    object TabSheet1: TTabSheet
      Caption = 'Tapety'
      object Image1: TImage
        Left = 128
        Top = 216
        Width = 193
        Height = 73
        Align = alCustom
        Center = True
        ParentShowHint = False
        Proportional = True
        ShowHint = False
      end
      object ListBox1: TListBox
        Left = 8
        Top = 4
        Width = 417
        Height = 208
        BevelInner = bvSpace
        BevelKind = bkFlat
        BorderStyle = bsNone
        Color = clWhite
        Ctl3D = True
        ExtendedSelect = False
        IntegralHeight = True
        ItemHeight = 13
        ParentCtl3D = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = sdf
      end
      object Button6: TButton
        Left = 328
        Top = 260
        Width = 89
        Height = 21
        Caption = 'Usu'#324' wszystko'
        TabOrder = 1
        OnClick = Button6Click
      end
      object Button5: TButton
        Left = 16
        Top = 236
        Width = 105
        Height = 21
        Caption = 'Dodaj'
        ParentShowHint = False
        ShowHint = False
        TabOrder = 2
        OnClick = Button5Click
      end
      object Button2: TButton
        Left = 16
        Top = 260
        Width = 105
        Height = 21
        Caption = 'Dodaj katalog'
        TabOrder = 3
        OnClick = Button2Click
      end
      object Button1: TButton
        Left = 328
        Top = 236
        Width = 89
        Height = 21
        Caption = 'Usu'#324
        TabOrder = 4
        OnClick = Button1Click
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Opcje'
      ImageIndex = 1
      object GroupBox1: TGroupBox
        Left = 120
        Top = 24
        Width = 177
        Height = 121
        Caption = 'Autostart'
        TabOrder = 0
        object Button3: TButton
          Left = 46
          Top = 32
          Width = 91
          Height = 25
          Caption = 'Dodaj'
          TabOrder = 0
          OnClick = Button3Click
        end
        object Button4: TButton
          Left = 46
          Top = 72
          Width = 91
          Height = 25
          Caption = 'Usu'#324
          TabOrder = 1
          OnClick = Button4Click
        end
      end
      object GroupBox2: TGroupBox
        Left = 120
        Top = 168
        Width = 177
        Height = 105
        Caption = 'Spos'#243'b wybierania tapet'
        TabOrder = 1
        object RadioButton1: TRadioButton
          Left = 32
          Top = 32
          Width = 113
          Height = 17
          Caption = 'Po kolei'
          TabOrder = 0
          OnClick = RadioButton1Click
        end
        object RadioButton2: TRadioButton
          Left = 32
          Top = 64
          Width = 113
          Height = 17
          Caption = 'Losowo'
          TabOrder = 1
          OnClick = RadioButton2Click
        end
      end
    end
    object TabSheet3: TTabSheet
      Caption = 'Informacje'
      ImageIndex = 2
      object Label1: TLabel
        Left = 288
        Top = 48
        Width = 33
        Height = 13
        Caption = 'ver.1.0'
      end
      object Label2: TLabel
        Left = 104
        Top = 16
        Width = 175
        Height = 56
        Caption = 'Tapeter'
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clNavy
        Font.Height = -48
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label3: TLabel
        Left = 176
        Top = 64
        Width = 56
        Height = 14
        Caption = 'FREEWARE'
        Font.Charset = EASTEUROPE_CHARSET
        Font.Color = clGray
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        ParentFont = False
      end
      object Label4: TLabel
        Left = 72
        Top = 112
        Width = 17
        Height = 13
        Caption = 'by: '
      end
      object Label5: TLabel
        Left = 96
        Top = 104
        Width = 138
        Height = 22
        Caption = 'Kamil Rudnicki'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -19
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label7: TLabel
        Left = 72
        Top = 144
        Width = 213
        Height = 16
        Caption = 'http://kamilrudnicki.w.interia.pl'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
      end
      object Label8: TLabel
        Left = 72
        Top = 160
        Width = 151
        Height = 16
        Caption = 'kamil1616@poczta.fm'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
      end
      object Memo1: TMemo
        Left = 32
        Top = 232
        Width = 273
        Height = 49
        BorderStyle = bsNone
        Color = clActiveBorder
        Lines.Strings = (
          'Jest to program typu FREEWARE.'
          'Rozprowadzanie go jest mile widziane. Wszelkie pytania, '
          'uwagi i sugestie prosz'#281' kierowa'#263' na m'#243'j adres.')
        TabOrder = 0
      end
    end
  end
  object OpenPictureDialog1: TOpenPictureDialog
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    Left = 376
  end
end
