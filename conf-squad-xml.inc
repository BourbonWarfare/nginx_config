# Homepage configuration.
server {
    listen       443 ssl;
    server_name squad.bourbonwarfare.com squad.bwarma.com;
    http2 on;

    include B:/web/_configs/nginx_config/conf-anubis.inc;
}

server {
    listen       3000;
    
    server_name squad.bourbonwarfare.com squad.bwarma.com;

    port_in_redirect off;

    location / {
        proxy_pass https://hub.bourbonwarfare.com/auth/remarks;
    }
}