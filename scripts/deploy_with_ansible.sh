#!/bin/bash
echo "operator" | sudo -S ansible-playbook -i /etc/ansible/hosts playbook.yml -K