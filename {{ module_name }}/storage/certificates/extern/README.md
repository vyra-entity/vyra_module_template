# External Module Certificates

This directory stores certificates from external modules that need to authenticate
or authorize themselves with this module.

## Usermanager Certificates

External usermanager modules can place their certificate here to authorize themselves
as the primary usermanager for this module instance.

Example:
- `extern/usermanager_<module_id>.crt` - Certificate from external usermanager
- `extern/usermanager_<module_id>.key` - Private key (if needed)

Only usermanager modules with valid certificates in this directory will be recognized
as authorized external usermanager services.

## Directory Structure

```
certificates/
├── redis/          # Redis SSL certificates
├── grpc/           # gRPC SSL certificates  
└── extern/         # External module certificates (this directory)
    ├── README.md
    └── usermanager_<module_id>.crt  # Example external usermanager cert
```
