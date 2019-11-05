#!/bin/bash
echo "operador" | sudo -S ansible-playbook -i /etc/ansible/hosts ../playbook/playbook.yml -K