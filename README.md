### 2024-06-29

#### 运行报错

```cmd
qt.network.ssl: QSslSocket: cannot resolve EVP_PKEY_base_id
qt.network.ssl: QSslSocket: cannot resolve SSL_get_peer_certificate
```
#### 原因

本地OpenSSL版本与Qt支持的OpenSSL版本不一致。