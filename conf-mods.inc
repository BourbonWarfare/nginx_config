# Homepage configuration.
server {
    listen       443 ssl;
    server_name mods.bourbonwarfare.com mods.bwarma.com;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name mods.bourbonwarfare.com mods.bwarma.com;

    port_in_redirect off;

    location / {
        index index.html;
    }
    
    location /core {
        try_files $uri $uri.html $uri/ =404;
        index core.html;
    }
}