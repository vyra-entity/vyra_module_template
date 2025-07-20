### Registration Process

There is a vyra modulemanager that is the one and only sro2 certificate authentication to sign certificates and permission files.

The modulemanager will create a default minimual permission.p7s file which allows a node to publish on a given registration topic.

Regarding this, the registratio process is as follows:

Registration preparation:
- The modulemanager will startup at first module
- It will generate the minimal permission.p7s file 
- This file will be copied to a safe space and must be loaded from each module in the docker file 
- The module starts with this minimum permission

Registration:
1. The module send a request to the registration process with (new_permission_file, certificate_to_be_signed)
2. If the module is not on blacklist "it could be authenticated"
3. Response (Signed_certificate, signed_permission)
4. Node can now present its services and actions and publications and subscriptions on its topics
