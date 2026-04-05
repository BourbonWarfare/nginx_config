# Homepage configuration.
server {
    listen       443 ssl;
    server_name  wiki.bourbonwarfare.com wiki.bwarma.com wiki.bourbonwarfare.club;
    http2 on;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name  wiki.bourbonwarfare.com wiki.bwarma.com wiki.bourbonwarfare.club;

    port_in_redirect off;

    location / {
        root   B:/web/mediawiki/current/;
        index  index.html index.htm;
    }
}