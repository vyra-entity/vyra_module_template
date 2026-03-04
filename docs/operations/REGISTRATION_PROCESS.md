### Registration Process

There is a vyra modulemanager that is the one and only sro2 certificate authentication to sign certificates and permission files.

The modulemanager will create a default minimual permission.p7s file which allows a node to publish on a given registration topic.

Regarding this, the registratio process is as follows:

Registration preparation:
- The modulemanager will startup at first module
- Module registration access either A or B:    
    - A) The modulemanager has a small webinterface to register new modules. 
    - B) A Userinterface is already connected and the registration process is done automatically
- Once the registration is received, the permissions.p7s and identity.ca.cert.pem files could be downloaded directly an and installed in the new module
- This permissions.p7s has the base configurations to do some basic functionallities and also has the request_permission_signature function that is responsible for signing a new permission file to grant more access to this module
- A module will therefore be request a new permissions for their own functionalities 

Registration:
1. The module send a request to the registration process with (new_permission_file, certificate_to_be_signed)
2. If the module is not on blacklist "it could be authenticated"
3. Response (Signed_certificate, signed_permission)
4. Node can now present its services and actions and publications and subscriptions on its topics
