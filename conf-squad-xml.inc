# Homepage configuration.
server {
    listen       443 ssl;
    server_name squad.bourbonwarfare.com squad.bwarma.com;

    include B:/web/_configs/nginx_config/conf-anubis.inc";
}

server {
    listen       3000;
    
    server_name squad.bourbonwarfare.com squad.bwarma.com;

    port_in_redirect off;
    root B:/web/bourbonwarfare.com/squad/;

    location / {
        # phpbb uses index.htm
        index squad.php;
        try_files $uri $uri/ @rewriteapp;
    }
    
    # Pass the php scripts to fastcgi server specified in upstream declaration.
    location ~ \.php(/|$) {
        # Unmodified fastcgi_params from nginx distribution.
        include fastcgi_params;
        # Necessary for php.
        fastcgi_split_path_info ^(.+\.php)(/.*)$;
        fastcgi_param PATH_INFO $fastcgi_path_info;
        fastcgi_param SCRIPT_FILENAME $realpath_root$fastcgi_script_name;
        fastcgi_param DOCUMENT_ROOT $realpath_root;
        try_files $uri $uri/ /app.php$is_args$args;
        fastcgi_pass php;
    }
}