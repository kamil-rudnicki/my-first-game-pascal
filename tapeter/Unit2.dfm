object Form2: TForm2
  Left = 219
  Top = 149
  BorderStyle = bsDialog
  Caption = 'Dodaj katalog'
  ClientHeight = 297
  ClientWidth = 434
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 120
    Top = 264
    Width = 73
    Height = 25
    Caption = 'Dodaj'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 224
    Top = 264
    Width = 73
    Height = 25
    Caption = 'Anuluj'
    TabOrder = 1
    OnClick = Button2Click
  end
  object DriveComboBox1: TDriveComboBox
    Left = 8
    Top = 8
    Width = 273
    Height = 19
    DirList = DirectoryListBox1
    TabOrder = 2
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 8
    Top = 32
    Width = 273
    Height = 193
    FileList = FileListBox1
    ItemHeight = 16
    TabOrder = 3
    OnChange = DirectoryListBox1Change
  end
  object FilterComboBox1: TFilterComboBox
    Left = 320
    Top = 72
    Width = 89
    Height = 21
    FileList = FileListBox1
    Filter = 'Bitmaps (*.bmp)|*.bmp'
    TabOrder = 4
    Visible = False
  end
  object FileListBox1: TFileListBox
    Left = 288
    Top = 8
    Width = 137
    Height = 217
    ItemHeight = 13
    Mask = '*.bmp'
    TabOrder = 5
  end
  object Edit1: TEdit
    Left = 8
    Top = 232
    Width = 417
    Height = 21
    TabOrder = 6
  end
end
