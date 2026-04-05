# Homepage configuration.
server {
    listen       443 ssl;
    server_name  bourbonwarfare.com bwarma.com bourbonwarfare.club;

    include "conf-anubis.inc"
}

server {
    listen       3000;
    
    server_name  bourbonwarfare.com bwarma.com bourbonwarfare.club;

    port_in_redirect off;

    location / {
        root   B:/web/bourbonwarfare.com/;
        index  index.html index.htm;
    }

    location /a3missions/ { # this is for the a3 mission downloads from in-game (Added June 2025)
        alias  B:/gameservers/arma/missions/main/;
    }
}