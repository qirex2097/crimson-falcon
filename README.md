# min_shell
7.17~
8.9~
# Minishell プロジェクトの要件

## 基本機能
- [x] プロンプトの表示
- [x] 履歴機能の実装
- [x] 実行可能ファイルの検索と起動（PATHまたは相対/絶対パス）
- [x] シグナル受信用のグローバル変数を1つのみ使用

## クォートの処理
- [x] 'シングルクォート'の処理
- [x] "ダブルクォート"の処理（$は例外）

## リダイレクトの実装
- [x] < 入力リダイレクト
- [x] > 出力リダイレクト
- [x] << ヒアドキュメント
- [x] >> 追記モードの出力リダイレクト

## その他の機能
- [x] パイプ（|）の実装
- [x] 環境変数（$）の展開
- [x] $?（直前のコマンドの終了ステータス）の処理

## シグナル処理
- [x] Ctrl-C、Ctrl-D、Ctrl-\の適切な処理

## ビルトインコマンドの実装
- [x] echo（-nオプション付き）
- [x] cd（相対パスまたは絶対パス）
- [x] pwd（オプションなし）
- [ ] export（オプションなし）
- [ ] unset（オプションなし）
- [x] env（オプションや引数なし）
- [ ] exit（オプションなし）

## その他の要件
- [ ] メモリリークの防止（readlineを除く）
- [ ] Makefileの作成（NAME, all, clean, fclean, re ルールを含む）