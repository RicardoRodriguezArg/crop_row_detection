pipeline {
    agent any

    stages {
        stage('Build Map Compiler Site') {
            steps {
                dir('map_compiler/website')
                {
                echo 'Building Python WebSite'
                sh 'python setup.py sdist'

                }
                
            }
        }
        stage('Test') {
            steps {
                echo 'Testing..'
            }
        }
        stage('Ansible - Deploy web site') {

            steps {
                echo 'Executing Deploying Scripts'
                dir('scripts')
                {
                    echo 'Preparing Map compiler enviroment'
                    echo 'Applying execution rigths'
                    sh 'chmod +x ./deploy_with_ansible.sh'
                    echo 'Calling Ansibles scritps'
                    sh './deploy_with_ansible.sh'
                }//close Dir
            }//close steps
        }//close Stage deploy web site
        stage('Ansible - Deploy scritps for ODM docker installation') {

            steps {
                echo 'Executing ODM Deploy Scripts'
                dir('scripts')
                {
                      echo 'moving scripts to remote'
                      sh 'chmod +x ./deploy_odm_scripts.sh'
                      echo 'Calling Ansibles scritps'
                      sh './deploy_odm_scripts.sh'
                    
                }//close Script Dir
            }//close steps
        }//close Stage deploy web site

    }//close Stages
}//close Pipeline
