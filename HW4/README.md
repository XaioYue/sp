
#### `race.c` (未使用 mutex)

```
Initial balance: 500
Final balance: [不定值]
Race condition occurred! Final balance: [錯誤值]
```

在未使用 mutex 的版本中，由於多執行緒同時訪問和修改共享資源（帳戶餘額），會產生 race condition，導致最終的帳戶餘額不一致。

#### `norace.c` (使用 mutex)

```
Initial balance: 500
Final balance: 200500
```

在使用了 mutex 的版本中，透過 mutex 鎖住關鍵區域，保證了多執行緒訪問和修改共享資源時的互斥性，避免了 race condition，最終帳戶餘額保持一致。


