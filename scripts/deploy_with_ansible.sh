#!/bin/bash
echo $USER
export ANSIBLE_CONFIG=/etc/ansible/ansible.cfg
echo "operator" | sudo -S ansible-playbook -i /etc/ansible/hosts ../playbook/playbook.yml -K --key-file /var/lib/jenkins/.ssh/id_rsa