# wyuEngine
  本プロジェクトは[CMake](https://cmake.org/)を使って作成しています。

## 簡単な紹介
  DirectX 9.0cを使った自作エンジンです。2Dと3Dの機能実装しています。

## ビルド環境
c++14ビルドできるコンパイラ、Cmakeバージョン3.19以上

## 実行環境

Win10,Win11

## 使用方法
build.batを実行してください。このバッチファイルはプロジェクトを生成し、wyuEngineのDebug構成を自動的にビルドします。

また、以下のコマンドを使用して最初にVisual Studioプロジェクトを生成し、ビルドディレクトリ内のソリューションを開いて手動でビルドすることもできます。
```
cmake -B build

cmake --build build --config Debug
```

## 外部ライブラリー
1. DirectX 9.0c
2. xaudio2
3. DirectInput／XInput
4. [Dear ImGui](https://github.com/ocornut/imgui)
5. [json11](https://github.com/dropbox/json11)

## エンジンフォルダの説明

1. engine/3rdparty
外部ライブラリーを保存用フォルダ

2. engine/include
エンジンヘッダファイルを保存用フォルダ

### engine/source
エンジンソースファイルを保存用フォルダ

## ソースコード説明
wyuEngineは拡張性のために仮想基底クラス多く使われてます、下の構造図を参考してください。

### 構造図
<p align="center">
    <img src="構造図.png"  alt="構造図">
  </a>
</p>

## エンジンの使用方法
Demoフォルダのソースコートにコメント書いてますので参考してください。
### フォルダの説明
#### Demo
1. Demo/include
アプリケーションヘッダファイルを保存用フォルダ
2. Demo/source
アプリケーションソースファイルを保存用フォルダ
3. Demo/asset
アプリケーションのアセットを保存用フォルダ
4. Demo/configs
アプリケーションの設定とフォルダのパスなどを設定するsetting.iniファイルを格納する場合。
5. Demo/configs/deployment
書き出した実行ファイルに使う設定
6. Demo/configs/development
デバッグの時に使う設定
7. Demo/bin
書き出した実行ファイルを保存用フォルダ

#### game
2DシューティングゲームのDemo、フォルダの構造は上と同じです。
