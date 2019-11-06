#!/bin/bash
echo $USER
echo $USER
export ANSIBLE_CONFIG=/etc/ansible/ansible.cfg
su - ci_operator
sudo ansible-playbook --user ci_operator -i /etc/ansible/hosts ../playbook/playbook.yml -K --key-file /home/ci_operator/.ssh/id_rsa -vvv