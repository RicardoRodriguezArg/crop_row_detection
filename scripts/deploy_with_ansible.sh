#!/bin/bash
echo $USER
su - ci_operator
echo $USER
export ANSIBLE_CONFIG=/etc/ansible/ansible.cfg
echo "operator" | sudo -S ansible-playbook --user ci_operator -i /etc/ansible/hosts ../playbook/playbook.yml -K --key-file /home/ci_operator/.ssh/id_rsa -vvv